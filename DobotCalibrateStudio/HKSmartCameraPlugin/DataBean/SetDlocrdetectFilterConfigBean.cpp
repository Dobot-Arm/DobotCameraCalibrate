#include "SetDlocrdetectFilterConfigBean.h"

bool CSetDlocrdetectFilterConfigRequestBean::fromJson(const QJsonObject &obj)
{
    key = obj["key"].toString();
    value = obj["value"].toString();
    return true;
}

QJsonObject CSetDlocrdetectFilterConfigRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("key", key);
    obj.insert("value", value);
    return obj;
}

bool CSetDlocrdetectFilterConfigRequestBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    QJsonArray parametertArr = obj["parameter"].toArray();
    for (int i=0; i<parametertArr.size(); ++i)
    {
        if (parametertArr[i].isObject())
        {
            CSetDlocrdetectFilterConfigRequestBean bean;
            bean.fromJson(parametertArr[i].toObject());
            parameter.append(bean);
        }
    }
    return true;
}

QJsonObject CSetDlocrdetectFilterConfigRequestBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    QJsonArray arr;
    for (int i=0; i<parameter.size(); ++i)
    {
        arr.append(parameter[i].toJsonObject());
    }
    obj.insert("parameter", arr);
    return obj;
}

bool CSetDlocrdetectFilterConfigRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetDlocrdetectFilterConfigRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetDlocrdetectFilterConfigResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetDlocrdetectFilterConfigResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetDlocrdetectFilterConfigResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetDlocrdetectFilterConfigResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
