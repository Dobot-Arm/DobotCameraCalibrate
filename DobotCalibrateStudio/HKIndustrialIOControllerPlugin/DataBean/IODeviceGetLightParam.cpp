#include "IODeviceGetLightParam.h"

bool CIODeviceGetLightParamRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("port") && obj["port"].isDouble()) port = obj["port"].toInt();
    if (obj.contains("channel") && obj["channel"].isDouble()) channel = obj["channel"].toInt();
    return true;
}

QJsonObject CIODeviceGetLightParamRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("port", port);
    obj.insert("channel", channel);
    return obj;
}

bool CIODeviceGetLightParamRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceGetLightParamRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CIODeviceGetLightParamResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("lightValue") && obj["lightValue"].isDouble()) lightValue = obj["lightValue"].toInt();
    if (obj.contains("duration") && obj["duration"].isDouble()) duration = obj["duration"].toInt();
    if (obj.contains("lightState") && obj["lightState"].isBool()) lightState = obj["lightState"].toBool();
    return true;
}

QJsonObject CIODeviceGetLightParamResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("lightValue", lightValue);
    obj.insert("duration", duration);
    obj.insert("lightState", lightState);
    return obj;
}

bool CIODeviceGetLightParamResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceGetLightParamResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
