#include "IODeviceLightTurnOn.h"

bool CIODeviceLightTurnOnRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("port") && obj["port"].isDouble()) port = obj["port"].toInt();
    if (obj.contains("channel") && obj["channel"].isDouble()) channel = obj["channel"].toInt();
    if (obj.contains("lightValue") && obj["lightValue"].isDouble()) lightValue = obj["lightValue"].toInt();
    if (obj.contains("duration") && obj["duration"].isDouble()) duration = obj["duration"].toInt();
    return true;
}

QJsonObject CIODeviceLightTurnOnRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("port", port);
    obj.insert("channel", channel);
    obj.insert("lightValue", lightValue);
    obj.insert("duration", duration);
    return obj;
}

bool CIODeviceLightTurnOnRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceLightTurnOnRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CIODeviceLightTurnOnResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceLightTurnOnResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CIODeviceLightTurnOnResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceLightTurnOnResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
