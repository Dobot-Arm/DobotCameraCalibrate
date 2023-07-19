#include "TcpServer.h"
#include <QNetworkProxy>
#include "DError.h"
#include "DefineMicro.h"
#include "NullDataBean.h"

CTcpServer::CTcpServer(QObject *parent) : IServerInterface(parent)
{
    m_pServer = new QTcpServer(this);
    m_pServer->setProxy(QNetworkProxy::NoProxy);
    connect(m_pServer, &QTcpServer::newConnection, this, &CTcpServer::slotNewConnection);
    connect(m_pServer, &QTcpServer::acceptError, this, [this](QAbstractSocket::SocketError socketError){
        qCritical()<<"tcp server acceptError:"<<socketError<<","<<m_pServer->errorString();
    });
}

CTcpServer::~CTcpServer()
{
    close();
}


QString CTcpServer::convertToClient(QTcpSocket* p)
{
    uint64_t senderId = reinterpret_cast<uint64_t>(p);
    return QString::number(senderId);
}

QTcpSocket* CTcpServer::convertToClient(QString strSenderId)
{
    uint64_t senderId = strSenderId.toULongLong();
    return reinterpret_cast<QTcpSocket*>(senderId);
}

bool CTcpServer::listen()
{
    bool bOk = false;
    if (!m_pServer->isListening())
    {
        bOk = m_pServer->listen(QHostAddress::Any, TCP_SERVER_PORT);
        if (!bOk)
        {
            qCritical()<<"tcp server listen error:"<<m_pServer->errorString();
        }
    }
    return bOk;
}

void CTcpServer::close()
{
    if (m_pServer->isListening())
    {
        m_pServer->close();
    }
    slotCloseServer();
}

void CTcpServer::slotNewConnection()
{
    while (m_pServer->hasPendingConnections())
    {
        QTcpSocket* pClient = m_pServer->nextPendingConnection();
        if (pClient)
        {
            qDebug()<<"a new tcp client has connected:"<<pClient
                   <<",name:"<<pClient->peerName()
                   <<",ip:"<<pClient->peerAddress().toString()
                   <<",port:"<<pClient->peerPort();

            m_allClient.insert(pClient,std::make_shared<QByteArray>());
            connect(pClient, &QTcpSocket::readyRead, this, &CTcpServer::slotClientRecvMsg);
            connect(pClient, &QTcpSocket::disconnected, this, &CTcpServer::slotClientDisconnect);
        }
    }

    return ;
}

void CTcpServer::slotCloseServer()
{
    QHash<QTcpSocket*,std::shared_ptr<QByteArray>> allClient = m_allClient;
    m_allClient.clear();

    for(auto itr=allClient.begin(); itr!=allClient.end(); ++itr)
    {
        itr.key()->abort();
        itr.key()->deleteLater();
    }
    allClient.clear();
    return ;
}

void CTcpServer::slotClientRecvMsg()
{
    QTcpSocket* pSender = qobject_cast<QTcpSocket*>(sender());

    //将数据缓存起来，组包
    auto itrFind = m_allClient.find(pSender);
    if (itrFind != m_allClient.end())
    {
        itrFind.value()->append(pSender->readAll());
    }
    else
    {
        qDebug()<<"[tcp recv]cannot find the sender";
        return ;
    }

    do
    {
        const QString strMsg = takePackage(pSender);
        if (strMsg.isEmpty())
        {
            return ;
        }
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(strMsg.toUtf8(), &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject())
        {
            qDebug()<<"[tcp recv]invalid json:<<<"<<strMsg;

            CNullDataBean result;
            CMessageResponse msg;
            msg.setId(0);
            msg.setCode(DT_ERR_INVALID_REQUEST);
            msg.setErrMsg(DError::getErrMsg(msg.getCode()));
            msg.setResult(result.toJsonObject());
            msg.setSenderId(convertToClient(pSender));

            sendMsgToClient(msg);
            return ;
        }

        QJsonObject obj = doc.object();
        if (obj.contains("id") && obj["id"].isDouble()
            && obj.contains("method") && obj["method"].isString()
            && obj.contains("params") && obj["params"].isObject())
        {//request msg
            CMessageRequest msg;
            msg.fromJson(obj);
            /*定的协议中是不存在msguuid和senderid字段，但是仍然要
             * 防止客户端发过来的消息体中也包含msguuid和senderid字段，
             * 所以这里强制覆盖，避免发生偷梁换柱、串消息现象。*/
            msg.setMsgUuid(createUuid());
            msg.setSenderId(convertToClient(pSender));

            sendMsgToPlugin(msg);
        }
        else
        {
            qCritical()<<"[tcp recv]invalid request,miss parameter:<<<"<<strMsg;

            CNullDataBean result;
            CMessageResponse msg;
            msg.fromJson(obj);
            msg.setCode(DT_ERR_INVALID_PARAMS);
            msg.setErrMsg(DError::getErrMsg(msg.getCode()));
            msg.setResult(result.toJsonObject());
            msg.setSenderId(convertToClient(pSender));

            sendMsgToClient(msg);
        }
    }while(true);
    return ;
}

void CTcpServer::slotClientDisconnect()
{
    auto pClient = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"a tcp client has closed:"<<pClient
           <<",name:"<<pClient->peerName()
           <<",ip:"<<pClient->peerAddress().toString()
           <<",port:"<<pClient->peerPort();

    m_allClient.remove(pClient);
    pClient->deleteLater();

    //客户端断开了连接，则通知所有插件
    emit signalClientHasDisconnected(convertToClient(pClient));

    return ;
}

void CTcpServer::sendMsgToClient(const CMessageResponse &msg)
{
    if (msg.isPrintLog()) qDebug()<<"[tcp send]>>>"<<msg.toJsonString();
    else
    {
        qDebug()<<"[tcp send]>>>doesn't print this message,msgid:"<<msg.getMsgUuid()<<",id:"<<msg.getId()
               <<",errcode:"<<msg.getCode()<<",errmsg:"<<msg.getErrMsg();
    }
    QTcpSocket* pClient = convertToClient(msg.getSenderId());
    if (m_allClient.contains(pClient))
    {
        QByteArray sendData = msg.toJsonStringSimple().toUtf8();
        sendData.append('\0');
        pClient->write(sendData);
    }
    else
    {
        qDebug()<<"the client("<<((void*)pClient)<<") of senderId("<<msg.getSenderId()<<") not found,send msg error!";
    }

    return ;
}

void CTcpServer::sendMsgToPlugin(const CMessageRequest &msg)
{
    qDebug()<<"[tcp recv]<<<"<<msg.toJsonString();
    emit signalDoRequestMsg(msg.toJsonObject());
}

QString CTcpServer::takePackage(QTcpSocket* pSender)
{
    auto ptr = m_allClient.value(pSender);
    if (ptr->isNull())
    {
        return "";
    }
    int iPos = ptr->indexOf('\0');
    if (iPos < 0)
    {//没有找到结束符，但是数据总长度超过了一定值，那可能就是连接被攻击，数据要清掉
        constexpr int nLimitSize = 2*1024*1024;
        if (ptr->size()>nLimitSize)
        {
            ptr->clear();
        }
        return "";
    }
    QByteArray data = ptr->left(iPos);
    ptr->remove(0,iPos+1);
    return QString(data);
}
