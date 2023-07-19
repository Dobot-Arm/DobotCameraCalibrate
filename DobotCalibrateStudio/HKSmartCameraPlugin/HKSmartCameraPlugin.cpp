#include "HKSmartCameraPlugin.h"
#include "JsonMessage.h"
#include "NullDataBean.h"
#include "DefineMicro.h"
#include "DobotDevice.h"

struct HKSmartCameraPluginPrivate
{
    //一个用户只能操作一个对象
    QHash<QString, //senderid
        CDobotDevice*
    > m_dobotDevice;
};

HKSmartCameraPlugin::HKSmartCameraPlugin(QObject *parent)
    :DobotInterfacePlugin(parent)
    ,m_ptr(new HKSmartCameraPluginPrivate)
{
}

HKSmartCameraPlugin::~HKSmartCameraPlugin()
{
    for(auto itr=m_ptr->m_dobotDevice.begin();itr!=m_ptr->m_dobotDevice.end();++itr)
    {
        itr.value()->deleteLater();
    }
    delete m_ptr;
}

QString HKSmartCameraPlugin::getVersion()
{
    QString strVersion = QString::asprintf("V-%s %s",__DATE__,__TIME__);
    return strVersion;
}

CDobotDevice* HKSmartCameraPlugin::getDobotDevice(QString strSenderId)
{
    CDobotDevice* pDevice = m_ptr->m_dobotDevice.value(strSenderId, nullptr);
    return pDevice;
}

CDobotDevice* HKSmartCameraPlugin::createDobotDeviceIfNotExist(QString strSenderId)
{
    CDobotDevice* pDevice = m_ptr->m_dobotDevice.value(strSenderId, nullptr);
    if (!pDevice)
    {
        pDevice = new CDobotDevice(this);
        connect(pDevice, &CDobotDevice::doResponseMsg, this, [this](QJsonObject obj){
            doResponseMsg(obj);
        });
        m_ptr->m_dobotDevice.insert(strSenderId, pDevice);
    }
    return pDevice;
}

void HKSmartCameraPlugin::deleteDobotDevice(QString strSenderId)
{
    auto itr = m_ptr->m_dobotDevice.find(strSenderId);
    if (itr != m_ptr->m_dobotDevice.end())
    {
        itr.value()->deleteLater();
        m_ptr->m_dobotDevice.erase(itr);
    }
}

void HKSmartCameraPlugin::slotDoRequest(QJsonObject obj)
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

void HKSmartCameraPlugin::doHandlerClientClosed(const CMessageRequest &msg)
{
    /*//client退出了，即使返回了消息，client也收不到，所以无需再返回消息了
    CNullDataBean result;
    CMessageResponse res(msg);
    res.setCode(DT_NO_ERROR);
    res.setErrMsg("");
    res.setResult(result.toJsonObject());
    doResponseMsg(res.toJsonObject());*/
    //QString strIdentify = msg.getParams().value("data").toObject().value("identify").toString();
    CDobotDevice* pDevice = getDobotDevice(msg.getSenderId());
    if (pDevice)
    {
        pDevice->closeNotResponse();
    }
    deleteDobotDevice(msg.getSenderId());
}

void HKSmartCameraPlugin::doHandlerDobotExit(const CMessageRequest &msg)
{
    /*//exe退出了，即使返回了消息，client也收不到，所以无需再返回消息了
    CNullDataBean result;
    CMessageResponse res(msg);
    res.setCode(DT_NO_ERROR);
    res.setErrMsg("");
    res.setResult(result.toJsonObject());
    doResponseMsg(res.toJsonObject());*/
    //QString strIdentify = msg.getParams().value("data").toObject().value("identify").toString();
    CDobotDevice* pDevice = getDobotDevice(msg.getSenderId());
    if (pDevice)
    {
        pDevice->closeNotResponse();
    }
    deleteDobotDevice(msg.getSenderId());
}

void HKSmartCameraPlugin::doHandlerCmd(const CMessageRequest &msg)
{
    //QString strIdentify = msg.getParams().value("data").toObject().value("identify").toString();
    createDobotDeviceIfNotExist(msg.getSenderId())->doCmd(msg);
}
