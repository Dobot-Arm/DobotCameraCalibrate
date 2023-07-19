#include "IODeviceClose.h"

bool CIODeviceCloseRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("port") && obj["port"].isDouble()) port = obj["port"].toInt();
    return true;
}

QJsonObject CIODeviceCloseRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("port", port);
    return obj;
}

bool CIODeviceCloseRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceCloseRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CIODeviceCloseResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceCloseResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CIODeviceCloseResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceCloseResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
