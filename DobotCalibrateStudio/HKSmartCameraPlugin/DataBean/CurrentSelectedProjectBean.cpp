#include "CurrentSelectedProjectBean.h"

bool CCurrentSelectedProjectRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CCurrentSelectedProjectRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CCurrentSelectedProjectRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCurrentSelectedProjectRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}


/*********************************************************************************************************/
/*********************************************************************************************************/
bool CCurrentSelectedProjectResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("name") && obj["name"].isString()) name = obj["name"].toString();
    return true;
}

QJsonObject CCurrentSelectedProjectResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("name",name);
    return obj;
}

bool CCurrentSelectedProjectResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCurrentSelectedProjectResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
