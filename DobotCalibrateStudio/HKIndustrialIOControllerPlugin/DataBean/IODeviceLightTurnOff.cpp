#include "IODeviceLightTurnOff.h"

bool CIODeviceLightTurnOffRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("port") && obj["port"].isDouble()) port = obj["port"].toInt();
    if (obj.contains("channel") && obj["channel"].isDouble()) channel = obj["channel"].toInt();
    return true;
}

QJsonObject CIODeviceLightTurnOffRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("port", port);
    obj.insert("channel", channel);
    return obj;
}

bool CIODeviceLightTurnOffRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceLightTurnOffRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CIODeviceLightTurnOffResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceLightTurnOffResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CIODeviceLightTurnOffResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceLightTurnOffResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
