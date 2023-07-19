#include "GetOutputCfgPrjResultCategoryBean.h"

bool CGetOutputConfigProjectResultCategoryRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetOutputConfigProjectResultCategoryRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetOutputConfigProjectResultCategoryRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCategoryRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOutputConfigProjectResultCategoryResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("value") && obj["value"].isDouble()) value = obj["value"].toInt();
    if (obj.contains("supportValues") && obj["supportValues"].isArray())
    {
        QJsonArray arr = obj["supportValues"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            supportValues.append(arr.at(i).toInt());
        }
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCategoryResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("value", (int)value);
    QJsonArray arr;
    for(int i=0;i<supportValues.size();++i)
    {
        arr.append((int)supportValues.at(i));
    }
    obj.insert("supportValues", arr);
    return obj;
}

bool CGetOutputConfigProjectResultCategoryResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCategoryResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
