#include "WebsocketServer.h"
#include <QNetworkProxy>
#include "DError.h"
#include "DefineMicro.h"
#include "NullDataBean.h"

CWebsocketServer::CWebsocketServer(QObject *parent) : IServerInterface(parent)
{
    m_pServer = new QWebSocketServer("DobotCalibrateServer20221130171423", QWebSocketServer::NonSecureMode, this);
    m_pServer->setProxy(QNetworkProxy::NoProxy);
    connect(m_pServer, &QWebSocketServer::newConnection, this, &CWebsocketServer::slotNewConnection);
    connect(m_pServer, &QWebSocketServer::closed, this, &CWebsocketServer::slotCloseServer);
    connect(m_pServer, &QWebSocketServer::closed, this, &CWebsocketServer::slotCloseServer);
    connect(m_pServer, &QWebSocketServer::acceptError, this, [this](QAbstractSocket::SocketError socketError){
        qCritical()<<"ws server acceptError:"<<socketError<<","<<m_pServer->errorString();
    });
    connect(m_pServer, &QWebSocketServer::serverError, this, [this](QWebSocketProtocol::CloseCode closeCode){
        qCritical()<<"ws server serverError:"<<closeCode<<","<<m_pServer->errorString();
    });
}

CWebsocketServer::~CWebsocketServer()
{
    close();
}

QString CWebsocketServer::convertToClient(QWebSocket* p)
{
    uint64_t senderId = reinterpret_cast<uint64_t>(p);
    return QString::number(senderId);
}

QWebSocket* CWebsocketServer::convertToClient(QString strSenderId)
{
    uint64_t senderId = strSenderId.toULongLong();
    return reinterpret_cast<QWebSocket*>(senderId);
}

bool CWebsocketServer::listen()
{
    bool bOk = false;
    if (!m_pServer->isListening())
    {
        bOk = m_pServer->listen(QHostAddress::Any, WEBSOCKET_SERVER_PORT);
        if (!bOk)
        {
            qCritical()<<"ws server listen error:"<<m_pServer->errorString();
        }
    }
    return bOk;
}

void CWebsocketServer::close()
{
    if (m_pServer->isListening())
    {
        m_pServer->close();
    }
}

void CWebsocketServer::slotNewConnection()
{
    while (m_pServer->hasPendingConnections())
    {
        QWebSocket* pClient = m_pServer->nextPendingConnection();
        if (pClient)
        {
            qDebug()<<"a new ws client has connected:"<<pClient
                   <<",name:"<<pClient->peerName()
                   <<",ip:"<<pClient->peerAddress().toString()
                   <<",port:"<<pClient->peerPort();

            m_allClient.insert(pClient);
            connect(pClient, &QWebSocket::textMessageReceived, this, &CWebsocketServer::slotClientRecvMsg);
            connect(pClient, &QWebSocket::disconnected, this, &CWebsocketServer::slotClientDisconnect);
        }
    }

    return ;
}

void CWebsocketServer::slotCloseServer()
{
    QList<QWebSocket*> allClient = m_allClient.toList();
    m_allClient.clear();
    for(auto itr=allClient.begin(); itr!=allClient.end(); ++itr)
    {
        (*itr)->abort();
        (*itr)->deleteLater();
    }

    return ;
}

void CWebsocketServer::slotClientRecvMsg(const QString &strMsg)
{
    QWebSocket* pSender = qobject_cast<QWebSocket*>(sender());

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(strMsg.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject())
    {
        qDebug()<<"[ws recv]invalid json:<<<"<<strMsg;

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
        qCritical()<<"[ws recv]invalid request,miss parameter:<<<"<<strMsg;

        CNullDataBean result;
        CMessageResponse msg;
        msg.fromJson(obj);
        msg.setCode(DT_ERR_INVALID_PARAMS);
        msg.setErrMsg(DError::getErrMsg(msg.getCode()));
        msg.setResult(result.toJsonObject());
        msg.setSenderId(convertToClient(pSender));

        sendMsgToClient(msg);
    }
    return ;
}

void CWebsocketServer::slotClientDisconnect()
{
    auto pClient = qobject_cast<QWebSocket*>(sender());
    qDebug()<<"a ws client has closed:"<<pClient
           <<",name:"<<pClient->peerName()
           <<",ip:"<<pClient->peerAddress().toString()
           <<",port:"<<pClient->peerPort();

    m_allClient.remove(pClient);
    pClient->deleteLater();

    //客户端断开了连接，则通知所有插件
    emit signalClientHasDisconnected(convertToClient(pClient));

    return ;
}

void CWebsocketServer::sendMsgToClient(const CMessageResponse &msg)
{
    if (msg.isPrintLog()) qDebug()<<"[ws send]>>>"<<msg.toJsonString();
    else
    {
        qDebug()<<"[ws send]>>>doesn't print this message,msgid:"<<msg.getMsgUuid()<<",id:"<<msg.getId()
               <<",errcode:"<<msg.getCode()<<",errmsg:"<<msg.getErrMsg();
    }
    QWebSocket* pClient = convertToClient(msg.getSenderId());
    if (m_allClient.contains(pClient))
    {
        pClient->sendTextMessage(msg.toJsonStringSimple());
    }
    else
    {
        qDebug()<<"the client("<<((void*)pClient)<<") of senderId("<<msg.getSenderId()<<") not found,send msg error!";
    }

    return ;
}

void CWebsocketServer::sendMsgToPlugin(const CMessageRequest &msg)
{
    qDebug()<<"[ws recv]<<<"<<msg.toJsonString();
    emit signalDoRequestMsg(msg.toJsonObject());
}
