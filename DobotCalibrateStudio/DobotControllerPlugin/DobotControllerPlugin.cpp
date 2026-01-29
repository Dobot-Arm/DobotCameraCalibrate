#include "DobotControllerPlugin.h"
#include "JsonMessage.h"
#include "NullDataBean.h"
#include "DefineMicro.h"
#include "DobotDevice.h"

struct DobotControllerPluginPrivate
{
    CDobotDevice* ptr;
};

DobotControllerPlugin::DobotControllerPlugin(QObject *parent)
    :DobotInterfacePlugin(parent)
    ,m_ptr(new DobotControllerPluginPrivate)
{
    m_ptr->ptr = new CDobotDevice(this);
    connect(m_ptr->ptr, &CDobotDevice::doResponseMsg, this, [this](QJsonObject obj){
        doResponseMsg(obj);
    });
}

DobotControllerPlugin::~DobotControllerPlugin()
{
    m_ptr->ptr->deleteLater();
    delete m_ptr;
}

QString DobotControllerPlugin::getVersion()
{
    QString strVersion = QString::asprintf("V-%s %s",__DATE__,__TIME__);
    return strVersion;
}

void DobotControllerPlugin::slotDoRequest(QJsonObject obj)
{
    CMessageRequest msg;
    msg.fromJson(obj);
    if (0 == msg.getMethod().compare(JSRPC_METHOD_INNER_CLIENT_CLOSED, Qt::CaseInsensitive))
    {
        doHandlerClientClosed(msg);
    }
    else if (0 == msg.getMethod().compare(JSRPC_METHOD_INNER_EXIT, Qt::CaseInsensitive))
    {
        doHandlerDobotExit(msg);
    }
    else
    {
        doHandlerCmd(msg);
    }
}

void DobotControllerPlugin::doHandlerClientClosed(const CMessageRequest &msg)
{//do nothing
    Q_UNUSED(msg);
}

void DobotControllerPlugin::doHandlerDobotExit(const CMessageRequest &msg)
{//do nothing
    Q_UNUSED(msg);
}

void DobotControllerPlugin::doHandlerCmd(const CMessageRequest &msg)
{
    m_ptr->ptr->doCmd(msg);
}
