#include "DobotDevice.h"
#include <memory>

#include "DError.h"
#include "HKIndustrialIODevice.h"
#include "NullDataBean.h"
#include "DataBean/IODeviceClose.h"
#include "DataBean/IODeviceGetLightParam.h"
#include "DataBean/IODeviceLightTurnOff.h"
#include "DataBean/IODeviceLightTurnOn.h"
#include "DataBean/IODeviceOpen.h"

CDobotDevice::CDobotDevice(QObject *parent) : QObject(parent)
{
    initFunctionMapper();
    m_bIsDeviceOpen.store(false);
    m_pIODevice = new HKIndustrialIODevice(this);
}

CDobotDevice::~CDobotDevice()
{
    closeNotResponse();
    m_pIODevice->deleteLater();
}

/*************************************************************************************************
 *************************************************************************************************/
void CDobotDevice::doCmd(const CMessageRequest &msg)
{
    if (m_mapperFunction.contains(msg.getApi()))
    {
        RequestJsonRpc rpc;
        rpc.strSenderId = msg.getSenderId();
        rpc.rpcId = msg.getId();
        rpc.strApi = msg.getApi();

        m_mtxRequestCacheId.lock();
        m_requestCacheId.insert(msg.getMsgUuid(),rpc);
        m_mtxRequestCacheId.unlock();

        auto pfn = m_mapperFunction.value(msg.getApi());
        (this->*pfn)(msg);
    }
    else
    {
        qDebug()<<"not find api:"<<msg.getApi();
        CNullDataBean result;
        CMessageResponse response(msg);
        response.setCode(DT_ERR_INVALID_METHOD);
        response.setErrMsg(DError::getErrMsg(response.getCode()));
        response.setResult(result.toJsonObject());
        emitResponseMsg(response);
    }
}

void CDobotDevice::emitResponseMsg(const CMessageResponse& msg)
{
    emit doResponseMsg(msg.toJsonObject(), QPrivateSignal());
}

void CDobotDevice::sendResponseSuccess(const QString &strMsgUuid, const CJsonMessage &responseData, bool bAutoDeleteCacheId/*=true*/)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    auto itr = m_requestCacheId.find(strMsgUuid);
    if (itr != m_requestCacheId.end())
    {
        CMessageResponse msg;
        msg.setId(itr.value().rpcId);
        msg.setCode(DT_NO_ERROR);
        msg.setErrMsg("");
        msg.setSenderId(itr.value().strSenderId);
        msg.setMsgUuid(strMsgUuid);
        msg.setResult(responseData.toJsonObject());
        msg.setPrintLog(responseData.isPrintLog());

        if (bAutoDeleteCacheId) m_requestCacheId.erase(itr);

        emitResponseMsg(msg);
    }
    else
    {
        qCritical()<<"not found msguuid("<<strMsgUuid<<"),can not response!!!!";
    }
}

void CDobotDevice::sendResponseError(const QString &strMsgUuid, const int iErrCode, const QString &strErrMsg, bool bAutoDeleteCacheId/*=true*/)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    auto itr = m_requestCacheId.find(strMsgUuid);
    if (itr != m_requestCacheId.end())
    {
        CNullDataBean result;
        CMessageResponse msg;
        msg.setId(itr.value().rpcId);
        msg.setCode(iErrCode);
        msg.setErrMsg(DError::getErrMsg(msg.getCode(), strErrMsg));
        msg.setSenderId(itr.value().strSenderId);
        msg.setMsgUuid(strMsgUuid);
        msg.setResult(result.toJsonObject());

        if (bAutoDeleteCacheId) m_requestCacheId.erase(itr);

        emitResponseMsg(msg);
    }
    else
    {
        qCritical()<<"not found msguuid("<<strMsgUuid<<"),can not response!!!!";
    }
}

void CDobotDevice::deleteAllCacheId()
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    m_requestCacheId.clear();
}

void CDobotDevice::deleteCacheId(const QString &strMsgUuid)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    m_requestCacheId.remove(strMsgUuid);
}

bool CDobotDevice::isDeviceOpen() const
{
    return m_bIsDeviceOpen.load();
}

void CDobotDevice::closeNotResponse()
{
    m_bIsDeviceOpen = false;
    m_pIODevice->closeDevice();
    deleteAllCacheId();
}

void CDobotDevice::open(const CMessageRequest &msg)
{
    CIODeviceOpenRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pIODevice->openDevice(request.m_data.port);

    CIODeviceOpenResponseResult result;
    if (ret)
    {
        m_bIsDeviceOpen = true;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        m_bIsDeviceOpen = false;
        sendResponseError(msg.getMsgUuid(), m_pIODevice->getErrCode(), m_pIODevice->getErrMessage());
    }
}

void CDobotDevice::close(const CMessageRequest &msg)
{
    m_bIsDeviceOpen = false;
    m_pIODevice->closeDevice();
    CIODeviceCloseResponseResult result;
    sendResponseSuccess(msg.getMsgUuid(), result);
    deleteAllCacheId();
}

void CDobotDevice::lightTurnOn(const CMessageRequest &msg)
{
    CIODeviceLightTurnOnRequestParams request;
    request.fromJson(msg.getParams());

    int iChannel = request.m_data.channel;
    int duration = request.m_data.duration;
    int lightValue = request.m_data.lightValue;

    bool ret = m_pIODevice->turnOnLight(iChannel, duration, lightValue);

    CIODeviceLightTurnOnResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pIODevice->getErrCode(), m_pIODevice->getErrMessage());
    }
}

void CDobotDevice::lightTurnOff(const CMessageRequest &msg)
{
    CIODeviceLightTurnOffRequestParams request;
    request.fromJson(msg.getParams());

    int iChannel = request.m_data.channel;

    bool ret = m_pIODevice->turnOffLight(iChannel);

    CIODeviceLightTurnOffResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pIODevice->getErrCode(), m_pIODevice->getErrMessage());
    }
}

void CDobotDevice::getLightParam(const CMessageRequest &msg)
{
    CIODeviceGetLightParamRequestParams request;
    request.fromJson(msg.getParams());

    int iChannel = request.m_data.channel;
    MV_IO_LIGHT_PARAM stLightParam;

    bool ret = m_pIODevice->getLightBoardParam(iChannel, stLightParam);

    CIODeviceGetLightParamResponseResult result;
    if (ret)
    {
        result.m_data.lightValue = stLightParam.nLightValue;
        result.m_data.duration = stLightParam.nDurationTime;
        result.m_data.lightState = stLightParam.nLightState==MV_IO_LIGHTSTATE::MV_IO_LIGHTSTATE_OFF;//这里很是奇怪，off表示亮
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pIODevice->getErrCode(), m_pIODevice->getErrMessage());
    }
}

