#include "HKIndustrialIOControllerPlugin.h"
#include "JsonMessage.h"
#include "NullDataBean.h"
#include "DefineMicro.h"
#include "DobotDevice.h"
#include "DError.h"

struct HKIndustrialIOControllerPluginPrivate
{
    //一个port只能对应一个device，反之亦然
    QHash<int, //port
        CDobotDevice*
    > m_dobotDevice;

    //一个senderid可以同时控制多个device，但是同一个device只能被一个人操作
    QHash<QString, //senderid
        QSet<int> //port
    > m_senderIds;
};

HKIndustrialIOControllerPlugin::HKIndustrialIOControllerPlugin(QObject *parent)
    :DobotInterfacePlugin(parent)
    ,m_ptr(new HKIndustrialIOControllerPluginPrivate)
{
}

HKIndustrialIOControllerPlugin::~HKIndustrialIOControllerPlugin()
{
    for(auto itr=m_ptr->m_dobotDevice.constBegin(); itr!=m_ptr->m_dobotDevice.constEnd(); ++itr)
    {
        itr.value()->closeNotResponse();
        itr.value()->deleteLater();
    }
    delete m_ptr;
}

QString HKIndustrialIOControllerPlugin::getVersion()
{
    QString strVersion = QString::asprintf("V-%s %s",__DATE__,__TIME__);
    return strVersion;
}

void HKIndustrialIOControllerPlugin::slotRecvDeviceMsg(QJsonObject obj)
{
    CDobotDevice* pDobotDevice = qobject_cast<CDobotDevice*>(sender());
    if (pDobotDevice && !pDobotDevice->isDeviceOpen())
    {
        CMessageResponse response;
        response.fromJson(obj);
        eraseDeviceIfNotOpen(pDobotDevice, response.getSenderId());
        pDobotDevice->deleteLater();
    }
    doResponseMsg(obj);
}

void HKIndustrialIOControllerPlugin::slotDoRequest(QJsonObject obj)
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

void HKIndustrialIOControllerPlugin::doHandlerClientClosed(const CMessageRequest &msg)
{
    //client退出了，即使返回了消息，client也收不到，所以无需再返回消息了
    //删除同一个senderid连接的所有设备
    QSet<int> allPorts = m_ptr->m_senderIds.value(msg.getSenderId(), QSet<int>());
    for(auto itr=allPorts.constBegin(); itr!=allPorts.constEnd(); ++itr)
    {
        CDobotDevice* pDobotDevice = m_ptr->m_dobotDevice.value(*itr, nullptr);
        if (pDobotDevice)
        {
            pDobotDevice->closeNotResponse();
            pDobotDevice->deleteLater();
            m_ptr->m_dobotDevice.remove(*itr);
        }
    }
    m_ptr->m_senderIds.remove(msg.getSenderId());
}

void HKIndustrialIOControllerPlugin::doHandlerDobotExit(const CMessageRequest &msg)
{
    Q_UNUSED(msg)
    //exe退出了，即使返回了消息，client也收不到，所以无需再返回消息了
    //断开所有的操作，并清空
    for(auto itr=m_ptr->m_dobotDevice.constBegin(); itr!=m_ptr->m_dobotDevice.constEnd(); ++itr)
    {
        itr.value()->closeNotResponse();
        itr.value()->deleteLater();
    }
    m_ptr->m_dobotDevice.clear();
    m_ptr->m_senderIds.clear();
}

void HKIndustrialIOControllerPlugin::doHandlerCmd(const CMessageRequest &msg)
{
    const int iPort = msg.getParams().value("data").toObject().value("port").toInt(-1);
    CDobotDevice* pDobotDevice = m_ptr->m_dobotDevice.value(iPort, nullptr);
    if (pDobotDevice)
    {
        //这里可以根据实际需要做特殊处理：防止用户A，操作了用户B的设备
        QSet<int> allPorts = m_ptr->m_senderIds.value(msg.getSenderId(), QSet<int>()); //获取senderid用户控制的设备port列表
        if (allPorts.contains(iPort))
        {
            pDobotDevice->doCmd(msg);
        }
        else
        {//不存在该设备，说明你在试图操作别人的设备。
            CNullDataBean result;
            CMessageResponse response(msg);
            response.setCode(DT_ERR_ILLEGAL_OPERATE_OTHER_DEVICE);
            response.setErrMsg(DError::getErrMsg(response.getCode()));
            response.setResult(result.toJsonObject());
            doResponseMsg(response.toJsonObject());
        }
    }
    else
    {//没找到，则说明还没有进行open操作
        if ("open" == msg.getApi())
        {
            pDobotDevice = new CDobotDevice(this);
            connect(pDobotDevice, &CDobotDevice::doResponseMsg, this, &HKIndustrialIOControllerPlugin::slotRecvDeviceMsg);
            m_ptr->m_dobotDevice.insert(iPort, pDobotDevice);
            {//保存senderid和port
                auto itrSenderId = m_ptr->m_senderIds.find(msg.getSenderId());
                if (itrSenderId != m_ptr->m_senderIds.end())
                {
                    itrSenderId.value().insert(iPort);
                }
                else
                {
                    m_ptr->m_senderIds.insert(msg.getSenderId(), QSet<int>{iPort});
                }
            }
            pDobotDevice->doCmd(msg);
        }
        else
        {//都没有进行open操作，其他肯定操作都是失败的，则直接返回
            CNullDataBean result;
            CMessageResponse response(msg);
            response.setCode(DT_ERR_NOT_CONNECT);
            response.setErrMsg(DError::getErrMsg(response.getCode()));
            response.setResult(result.toJsonObject());
            doResponseMsg(response.toJsonObject());
        }
    }
    return ;
}

void HKIndustrialIOControllerPlugin::eraseDeviceIfNotOpen(CDobotDevice* pDobotDevice, QString strSenderId)
{
    int iPort = -1;
    //移除device
    for(auto itr=m_ptr->m_dobotDevice.constBegin(); itr!=m_ptr->m_dobotDevice.constEnd(); ++itr)
    {
        if (pDobotDevice == itr.value())
        {
            iPort = itr.key();
            m_ptr->m_dobotDevice.erase(itr);
            break;
        }
    }

    //移除senderid中的port
    auto itrAllPorts = m_ptr->m_senderIds.find(strSenderId);
    if (itrAllPorts != m_ptr->m_senderIds.end())
    {
        itrAllPorts->remove(iPort);
        if (itrAllPorts->empty())
        {
            m_ptr->m_senderIds.erase(itrAllPorts);
        }
    }
}
