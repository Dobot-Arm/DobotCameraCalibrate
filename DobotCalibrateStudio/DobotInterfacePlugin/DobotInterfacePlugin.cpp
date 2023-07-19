#include "DobotInterfacePlugin.h"
#include "DobotInterfacePluginPrivate.h"

DobotInterfacePlugin::DobotInterfacePlugin(QObject *parent)
    : QObject(parent)
{
    m_ptr = new DobotInterfacePluginPrivate(this);
    connect(m_ptr, &DobotInterfacePluginPrivate::signalDoRequest, this, &DobotInterfacePlugin::slotDoRequest);
}

DobotInterfacePlugin::~DobotInterfacePlugin()
{
}

void DobotInterfacePlugin::doRequestMsg(const QJsonObject &obj)
{
    emit m_ptr->signalDoRequest(obj, DobotInterfacePluginPrivate::QPrivateSignal());
}

void DobotInterfacePlugin::doResponseMsg(const QJsonObject& obj)
{
    emit signalDoResponse(obj, QPrivateSignal());
}
