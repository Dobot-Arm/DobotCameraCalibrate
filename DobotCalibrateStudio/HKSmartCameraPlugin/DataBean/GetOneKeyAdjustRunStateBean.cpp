#include "GetOneKeyAdjustRunStateBean.h"

bool CGetOneKeyAdjustRunStateRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetOneKeyAdjustRunStateRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetOneKeyAdjustRunStateRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CGetOneKeyAdjustRunStateRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOneKeyAdjustRunStateResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("state") && obj["state"].isDouble()) state = obj["state"].toInt();
    return true;
}

QJsonObject CGetOneKeyAdjustRunStateResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("state",state);
    return obj;
}

bool CGetOneKeyAdjustRunStateResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOneKeyAdjustRunStateResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
