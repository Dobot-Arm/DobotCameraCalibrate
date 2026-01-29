#include "GetSetDeviceUserId.h"

bool GetDeviceUserIdRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject GetDeviceUserIdRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool GetDeviceUserIdRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject GetDeviceUserIdRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
bool GetDeviceUserIdResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("value") && obj["value"].isString()) value = obj["value"].toString();
    return true;
}

QJsonObject GetDeviceUserIdResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("value", value);
    return obj;
}

bool GetDeviceUserIdResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject GetDeviceUserIdResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool SetDeviceUserIdRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("value") && obj["value"].isString()) value = obj["value"].toString();
    return true;
}

QJsonObject SetDeviceUserIdRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("value", value);
    return obj;
}

bool SetDeviceUserIdRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject SetDeviceUserIdRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
bool SetDeviceUserIdResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject SetDeviceUserIdResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool SetDeviceUserIdResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject SetDeviceUserIdResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
