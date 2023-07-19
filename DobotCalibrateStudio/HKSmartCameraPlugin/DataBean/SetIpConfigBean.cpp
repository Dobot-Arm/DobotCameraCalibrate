#include "SetIpConfigBean.h"

bool CSetIpConfigRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("ip") && obj["ip"].isString()) ip = obj["ip"].toString();
    if (obj.contains("subnetmask") && obj["subnetmask"].isString()) subnetmask = obj["subnetmask"].toString();
    if (obj.contains("gateway") && obj["gateway"].isString()) gateway = obj["gateway"].toString();
    return true;
}

QJsonObject CSetIpConfigRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify",identify);
    obj.insert("ip",ip);
    obj.insert("subnetmask",subnetmask);
    obj.insert("gateway",gateway);
    return obj;
}

bool CSetIpConfigRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CSetIpConfigRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetIpConfigResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetIpConfigResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetIpConfigResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetIpConfigResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
