#ifndef CWEBSOCKETSERVER_H
#define CWEBSOCKETSERVER_H

#include "IServerInterface.h"

#include <QWebSocketServer>
#include <QWebSocket>
#include <QSet>

class CWebsocketServer : public IServerInterface
{
    Q_OBJECT
public:
    explicit CWebsocketServer(QObject *parent = nullptr);
    ~CWebsocketServer();

    bool listen() Q_DECL_OVERRIDE;
    void close() Q_DECL_OVERRIDE;

    //send msg to client
    void sendMsgToClient(const CMessageResponse& msg) Q_DECL_OVERRIDE;

private slots:
    void slotNewConnection();
    void slotCloseServer();
    void slotClientRecvMsg(const QString& strMsg);
    void slotClientDisconnect();

private:
    void sendMsgToPlugin(const CMessageRequest& msg);
    static QString convertToClient(QWebSocket* p);
    static QWebSocket* convertToClient(QString strSenderId);

private:
    QWebSocketServer* m_pServer;
    QSet<QWebSocket*> m_allClient;
};

#endif // CWEBSOCKETSERVER_H
