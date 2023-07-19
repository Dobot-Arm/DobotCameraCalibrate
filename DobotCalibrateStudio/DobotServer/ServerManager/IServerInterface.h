#ifndef ISERVERINTERFACE_H
#define ISERVERINTERFACE_H

#include <QObject>

#include "JsonMessage.h"

class IServerInterface : public QObject
{
    Q_OBJECT
public:
    explicit IServerInterface(QObject*parent = nullptr):QObject(parent){};
    virtual ~IServerInterface(){};

    virtual bool listen() = 0;
    virtual void close() = 0;

    //send msg to client
    virtual void sendMsgToClient(const CMessageResponse& msg) = 0;

signals:
    void signalDoRequestMsg(const QJsonObject& obj);
    void signalClientHasDisconnected(QString strClientId);
};

#endif // ISERVERINTERFACE_H
