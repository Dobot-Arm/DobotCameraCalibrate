#include "GetCurrentProjectRunningStateBean.h"

bool CGetCurrentProjectRunningStateRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CGetCurrentProjectRunningStateRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CGetCurrentProjectRunningStateRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CGetCurrentProjectRunningStateRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetCurrentProjectRunningStateResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("state") && obj["state"].isBool()) state = obj["state"].toBool();
    return true;
}

QJsonObject CGetCurrentProjectRunningStateResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("state",state);
    return obj;
}

bool CGetCurrentProjectRunningStateResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetCurrentProjectRunningStateResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
