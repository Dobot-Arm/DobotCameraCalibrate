#include "CurrentProgressBean.h"

bool CCurrentProgressRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CCurrentProgressRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CCurrentProgressRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCurrentProgressRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}


/*********************************************************************************************************/
/*********************************************************************************************************/
bool CCurrentProgressResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("progress") && obj["progress"].isDouble()) progress = obj["progress"].toInt();
    if (obj.contains("status") && obj["status"].isBool()) status = obj["status"].toBool();
    return true;
}

QJsonObject CCurrentProgressResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("progress",progress);
    obj.insert("status",status);
    return obj;
}

bool CCurrentProgressResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCurrentProgressResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
