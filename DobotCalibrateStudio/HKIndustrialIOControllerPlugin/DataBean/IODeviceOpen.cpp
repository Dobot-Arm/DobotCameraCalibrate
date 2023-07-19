#include "IODeviceOpen.h"

bool CIODeviceOpenRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("port") && obj["port"].isDouble()) port = obj["port"].toInt();
    return true;
}

QJsonObject CIODeviceOpenRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("port", port);
    return obj;
}

bool CIODeviceOpenRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CIODeviceOpenRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CIODeviceOpenResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceOpenResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CIODeviceOpenResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CIODeviceOpenResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
