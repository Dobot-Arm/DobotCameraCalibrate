#include "SearchCameraBean.h"

bool CSearchCameraRequestBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSearchCameraRequestBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSearchCameraRequestParams::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSearchCameraRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CNetcardInfoBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("name") && obj["name"].isString()) name = obj["name"].toString();
    if (obj.contains("ip") && obj["ip"].isString()) ip = obj["ip"].toString();
    if (obj.contains("subnetmask") && obj["subnetmask"].isString()) subnetmask = obj["subnetmask"].toString();
    if (obj.contains("gateway") && obj["gateway"].isString()) gateway = obj["gateway"].toString();
    if (obj.contains("mac") && obj["mac"].isString()) mac = obj["mac"].toString();
    return true;
}

QJsonObject CNetcardInfoBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("name",name);
    obj.insert("ip",ip);
    obj.insert("subnetmask",subnetmask);
    obj.insert("gateway",gateway);
    obj.insert("mac",mac);
    return obj;
}
/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSearchCameraResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("ip") && obj["ip"].isString()) ip = obj["ip"].toString();
    if (obj.contains("mac") && obj["mac"].isString()) mac = obj["mac"].toString();
    if (obj.contains("subnetmask") && obj["subnetmask"].isString()) subnetmask = obj["subnetmask"].toString();
    if (obj.contains("gateway") && obj["gateway"].isString()) gateway = obj["gateway"].toString();
    if (obj.contains("sn") && obj["sn"].isString()) sn = obj["sn"].toString();
    if (obj.contains("manufacturer") && obj["manufacturer"].isString()) manufacturer = obj["manufacturer"].toString();
    if (obj.contains("version") && obj["version"].isString()) version = obj["version"].toString();
    if (obj.contains("modelname") && obj["modelname"].isString()) modelname = obj["modelname"].toString();
    if (obj.contains("accessible") && obj["accessible"].isBool()) accessible = obj["accessible"].toBool();
    if (obj.contains("netcardinfo") && obj["netcardinfo"].isObject())
    {
        netcardinfo.fromJson(obj["netcardinfo"].toObject());
    }

    return true;
}

QJsonObject CSearchCameraResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify",identify);
    obj.insert("ip",ip);
    obj.insert("mac",mac);
    obj.insert("subnetmask",subnetmask);
    obj.insert("gateway",gateway);
    obj.insert("sn",sn);
    obj.insert("manufacturer",manufacturer);
    obj.insert("version",version);
    obj.insert("modelname",modelname);
    obj.insert("accessible",accessible);
    obj.insert("netcardinfo", netcardinfo.toJsonObject());
    return obj;
}

bool CSearchCameraResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CSearchCameraResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CSearchCameraResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}
