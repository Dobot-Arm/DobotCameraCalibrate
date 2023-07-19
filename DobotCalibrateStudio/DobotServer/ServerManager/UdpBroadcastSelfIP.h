#ifndef CUDPBROADCASTSELFIP_H
#define CUDPBROADCASTSELFIP_H

#include "IServerInterface.h"

class QUdpSocket;
class QTimer;

class CUdpBroadcastSelfIP : public IServerInterface
{
    Q_OBJECT
public:
    explicit CUdpBroadcastSelfIP(QObject *parent = nullptr);
    ~CUdpBroadcastSelfIP();

    bool listen() Q_DECL_OVERRIDE;
    void close() Q_DECL_OVERRIDE;

    //send msg to client
    void sendMsgToClient(const CMessageResponse& msg) Q_DECL_OVERRIDE;

private slots:
    void slotBroadcastIp();

private:
    QUdpSocket* m_pUdpSocket;
    QTimer* m_pTimer;
};

#endif // CUDPBROADCASTSELFIP_H
