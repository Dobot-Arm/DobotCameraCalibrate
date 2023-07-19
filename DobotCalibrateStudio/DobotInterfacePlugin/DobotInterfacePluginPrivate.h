#ifndef DOBOTINTERFACEPLUGINPRIVATE_H
#define DOBOTINTERFACEPLUGINPRIVATE_H

#include <QObject>
#include <QJsonObject>

#include "DobotInterfacePlugin.h"

class DobotInterfacePluginPrivate : public QObject
{
    Q_OBJECT

    friend class DobotInterfacePlugin;
public:
    DobotInterfacePluginPrivate(QObject* parent = nullptr):QObject(parent){};
    ~DobotInterfacePluginPrivate(){};

signals:
    void signalDoRequest(QJsonObject obj, QPrivateSignal);
};

#endif // DOBOTINTERFACEPLUGINPRIVATE_H
