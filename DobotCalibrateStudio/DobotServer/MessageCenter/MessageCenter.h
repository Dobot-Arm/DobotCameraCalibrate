#ifndef CMESSAGECENTER_H
#define CMESSAGECENTER_H

#include <QObject>
#include <atomic>
#include <QJsonObject>
#include <atomic>
#include <QHash>

class QThread;
class CMessageCenterPrivate;
class CPluginManager;
class IServerInterface;
class CWebsocketServer;
class CTcpServer;
class CUdpBroadcastSelfIP;
class CMessageRequest;

struct CMessageCenterPrivateData;

class CMessageCenter : public QObject
{
    Q_OBJECT
public:
    CMessageCenter(const CMessageCenter&) = delete;
    CMessageCenter(CMessageCenter&&) = delete;
    CMessageCenter& operator=(const CMessageCenter&) = delete;
    CMessageCenter& operator=(CMessageCenter&&) = delete;
    ~CMessageCenter();

    static CMessageCenter *getInstance();
    static void destroyInstance();

    //start ws server,and load plugin
    bool start();
    //stop ws server,and unload plugin
    void stop();

signals:
    void signalShowWindow();
    void signalHideWindow();
    void signalExitWindow();
    void signalLoggerOn(bool bOn);

private slots:
    void slotStart(bool* pIsFinished, bool* pResult);
    void slotStop(bool* pIsFinished);
    void slotWSClientHasDisconnected(QString strClientId);
    void slotTCPClientHasDisconnected(QString strClientId);

    void slotHandleWSRequestMsg(const QJsonObject& obj);
    void slotHandleTCPRequestMsg(const QJsonObject& obj);
    void slotHandlePluginResponseMsg(const QJsonObject& obj);

    void processApiRequest(const CMessageRequest& msg, IServerInterface* pServer);

private:
    explicit CMessageCenter(QObject *parent = nullptr);

    //删掉缓存信息
    void removeAllServerPointer(IServerInterface* pServer);

    //close this process
    void closeProcess();

private:
    CMessageCenterPrivateData* m_ptr;
};

#endif // CMESSAGECENTER_H
