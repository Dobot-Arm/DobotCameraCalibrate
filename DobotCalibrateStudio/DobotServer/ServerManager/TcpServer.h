#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include "IServerInterface.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QHash>
#include <QQueue>

class CTcpServer : public IServerInterface
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = nullptr);
    ~CTcpServer();

    bool listen() Q_DECL_OVERRIDE;
    void close() Q_DECL_OVERRIDE;

    //send msg to client
    void sendMsgToClient(const CMessageResponse& msg) Q_DECL_OVERRIDE;

private slots:
    void slotNewConnection();
    void slotCloseServer();
    void slotClientRecvMsg();
    void slotClientDisconnect();

private:
    void sendMsgToPlugin(const CMessageRequest& msg);
    static QString convertToClient(QTcpSocket* p);
    static QTcpSocket* convertToClient(QString strSenderId);

    QString takePackage(QTcpSocket* pSender);

private:
    QTcpServer* m_pServer;
    QHash<QTcpSocket*,std::shared_ptr<QByteArray>> m_allClient;
};

#endif // CTCPSERVER_H
