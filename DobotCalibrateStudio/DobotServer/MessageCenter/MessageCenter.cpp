#include "MessageCenter.h"
#include "MessageCenterPrivate.h"
#include "DError.h"
#include "DefineMicro.h"
#include "PluginManager/PluginManager.h"
#include "ServerManager/IServerInterface.h"
#include "ServerManager/WebsocketServer.h"
#include "ServerManager/TcpServer.h"
#include "ServerManager/UdpBroadcastSelfIP.h"

#include <QThread>
#include <QCoreApplication>

static CMessageCenter* g_MessageCenter = nullptr;
static QMutex g_mtxMsgCenter;

struct CMessageCenterPrivateData
{
    std::atomic_bool bIsStarted;
    CMessageCenterPrivate* pSignal;
    QThread* pThread;
    CPluginManager* pPluginMgr;
    CWebsocketServer* pWebsocketServer;
    CTcpServer* pTcpServer;
    CUdpBroadcastSelfIP* pUdpBroadcastSelfIP;

    //回消息时要知道是哪个server
    QHash<QString, //senderId,本来想存msgguid，但是视频数据流是主动推送的，导致后面数据无法找到IServerInterface*
        IServerInterface*
    > ServerPointer;
};

CMessageCenter::CMessageCenter(QObject *parent) : QObject(parent)
{
    m_ptr = new CMessageCenterPrivateData();

    m_ptr->pSignal = new CMessageCenterPrivate();
    connect(m_ptr->pSignal, &CMessageCenterPrivate::signalStart, this, &CMessageCenter::slotStart);
    connect(m_ptr->pSignal, &CMessageCenterPrivate::signalStop, this, &CMessageCenter::slotStop);

    m_ptr->bIsStarted = false;

    m_ptr->pThread = new QThread();
    this->moveToThread(m_ptr->pThread);

    m_ptr->pSignal->moveToThread(m_ptr->pThread);

    m_ptr->pPluginMgr = new CPluginManager();
    m_ptr->pPluginMgr->moveToThread(m_ptr->pThread);

    m_ptr->pWebsocketServer = new CWebsocketServer();
    m_ptr->pWebsocketServer->moveToThread(m_ptr->pThread);

    m_ptr->pTcpServer = new CTcpServer();
    m_ptr->pTcpServer->moveToThread(m_ptr->pThread);

    m_ptr->pUdpBroadcastSelfIP = new CUdpBroadcastSelfIP();
    m_ptr->pUdpBroadcastSelfIP->moveToThread(m_ptr->pThread);

    //msg from client to plugin
    connect(m_ptr->pWebsocketServer, &CWebsocketServer::signalDoRequestMsg,
            this, &CMessageCenter::slotHandleWSRequestMsg);
    connect(m_ptr->pTcpServer, &CTcpServer::signalDoRequestMsg,
            this, &CMessageCenter::slotHandleTCPRequestMsg);
    //msg from plugin to client
    connect(m_ptr->pPluginMgr, &CPluginManager::signalDoResponseMsg,
            this, &CMessageCenter::slotHandlePluginResponseMsg);

    //msg from client to this, all client has disconnect
    connect(m_ptr->pWebsocketServer, &CWebsocketServer::signalClientHasDisconnected,
            this, &CMessageCenter::slotWSClientHasDisconnected);
    connect(m_ptr->pTcpServer, &CTcpServer::signalClientHasDisconnected,
            this, &CMessageCenter::slotTCPClientHasDisconnected);

    /**********************************************************/
    //start thread and loop event
    m_ptr->pThread->start();
}

CMessageCenter::~CMessageCenter()
{
    qDebug()<<"message center will be destroy!";

    m_ptr->pThread->quit();
    m_ptr->pThread->terminate();
    m_ptr->pThread->wait();
    m_ptr->pThread->deleteLater();

    m_ptr->pPluginMgr->deleteLater();
    m_ptr->pWebsocketServer->deleteLater();
    m_ptr->pTcpServer->deleteLater();
    m_ptr->pUdpBroadcastSelfIP->deleteLater();
    m_ptr->pSignal->deleteLater();

    m_ptr->ServerPointer.clear();

    delete m_ptr;

    qDebug()<<"message center has destroyed!";
}

CMessageCenter *CMessageCenter::getInstance()
{
    if (!g_MessageCenter)
    {
        QMutexLocker guard(&g_mtxMsgCenter);
        if (!g_MessageCenter)
        {
            g_MessageCenter = new CMessageCenter;
        }
    }
    return g_MessageCenter;
}

void CMessageCenter::destroyInstance()
{
    if (g_MessageCenter)
    {
        QMutexLocker guard(&g_mtxMsgCenter);
        if (g_MessageCenter)
        {
            auto ptr = g_MessageCenter;
            g_MessageCenter = nullptr;
            ptr->deleteLater();
        }
    }
}

bool CMessageCenter::start()
{
    bool bIsFinished = false;
    bool bIsSuccess = false;

    if (!m_ptr->bIsStarted)
    {
        emit m_ptr->pSignal->signalStart(&bIsFinished, &bIsSuccess);
        while (!bIsFinished)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
        }
        m_ptr->bIsStarted = bIsSuccess;
    }
    return bIsSuccess;
}

void CMessageCenter::stop()
{
    if (m_ptr->bIsStarted)
    {
        bool bIsFinished = false;
        emit m_ptr->pSignal->signalStop(&bIsFinished);
        while (!bIsFinished)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
        }
    }
}

void CMessageCenter::slotStart(bool* pIsFinished, bool* pResult)
{
    bool bOk1 = m_ptr->pWebsocketServer->listen();
    bool bOk2 = m_ptr->pTcpServer->listen();
    bool bOk3 = m_ptr->pUdpBroadcastSelfIP->listen();
    *pResult = bOk1 || bOk2 || bOk3;
    *pIsFinished = true;
}

void CMessageCenter::slotStop(bool* pIsFinished)
{
    m_ptr->pWebsocketServer->close();
    m_ptr->pTcpServer->close();
    m_ptr->pUdpBroadcastSelfIP->close();
    m_ptr->ServerPointer.clear();

    *pIsFinished = true;
}

void CMessageCenter::slotWSClientHasDisconnected(QString strClientId)
{
    CMessageRequest msg;
    msg.setId(0);
    msg.setMethod(JSRPC_METHOD_INNER_CLIENT_CLOSED);
    msg.setParams(QJsonObject());
    msg.setSenderId(strClientId);

    m_ptr->pPluginMgr->sendAllRequestMsg(msg);
    removeAllServerPointer(m_ptr->pWebsocketServer);
}

void CMessageCenter::slotTCPClientHasDisconnected(QString strClientId)
{
    CMessageRequest msg;
    msg.setId(0);
    msg.setMethod(JSRPC_METHOD_INNER_CLIENT_CLOSED);
    msg.setParams(QJsonObject());
    msg.setSenderId(strClientId);

    m_ptr->pPluginMgr->sendAllRequestMsg(msg);
    removeAllServerPointer(m_ptr->pTcpServer);
}

void CMessageCenter::slotHandleWSRequestMsg(const QJsonObject &obj)
{
    CMessageRequest msg;
    msg.fromJson(obj);
    if (msg.getMethod().startsWith("dobot.api."))
    {
        processApiRequest(msg, m_ptr->pWebsocketServer);
    }
    else
    {
        m_ptr->ServerPointer.insert(msg.getSenderId(), m_ptr->pWebsocketServer);
        m_ptr->pPluginMgr->sendDoRequestMsg(msg);
    }
}

void CMessageCenter::slotHandleTCPRequestMsg(const QJsonObject &obj)
{
    CMessageRequest msg;
    msg.fromJson(obj);
    if (msg.getMethod().startsWith("dobot.api."))
    {
        processApiRequest(msg, m_ptr->pTcpServer);
    }
    else
    {
        m_ptr->ServerPointer.insert(msg.getSenderId(), m_ptr->pTcpServer);
        m_ptr->pPluginMgr->sendDoRequestMsg(msg);
    }
}

void CMessageCenter::processApiRequest(const CMessageRequest& msg, IServerInterface* pServer)
{
    int iErrCode = DT_NO_ERROR;
    if (msg.getMethod() == "dobot.api.show"){
        emit signalShowWindow();
    }else if (msg.getMethod() == "dobot.api.hide"){
        emit signalHideWindow();
    }else if (msg.getMethod() == "dobot.api.exit"){
        emit signalExitWindow();
        return ;
    }else if (msg.getMethod() == "dobot.api.loggeron"){
        emit signalLoggerOn(true);
    }else if (msg.getMethod() == "dobot.api.loggeroff"){
        emit signalLoggerOn(false);
    }else{
        iErrCode = DT_ERR_INVALID_METHOD;
    }

    CMessageResponse response(msg);
    response.setCode(iErrCode);
    response.setErrMsg(DError::getErrMsg(response.getCode()));
    pServer->sendMsgToClient(response);
}

void CMessageCenter::slotHandlePluginResponseMsg(const QJsonObject &obj)
{
    CMessageResponse msg;
    msg.fromJson(obj);
    IServerInterface* pServer = m_ptr->ServerPointer.value(msg.getSenderId(), nullptr);
    if (pServer)
    {
        pServer->sendMsgToClient(msg);
    }
}

void CMessageCenter::closeProcess()
{
    CMessageRequest msg;
    msg.setId(0);
    msg.setMethod(JSRPC_METHOD_INNER_EXIT);
    msg.setParams(QJsonObject());
    msg.setSenderId(0);

    m_ptr->pPluginMgr->sendAllRequestMsg(msg);
}

void CMessageCenter::removeAllServerPointer(IServerInterface* pServer)
{
    auto itr=m_ptr->ServerPointer.begin();
    while(itr!=m_ptr->ServerPointer.end())
    {
        if (itr.value() == pServer)
        {
            itr = m_ptr->ServerPointer.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
    return ;
}
