#include "GetTemplateRoiMatchPointBean.h"

bool CGetTemplateRoiMatchPointRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("matchPointXName") && obj["matchPointXName"].isString()) matchPointXName = obj["matchPointXName"].toString();
    if (obj.contains("matchPointYName") && obj["matchPointYName"].isString()) matchPointYName = obj["matchPointYName"].toString();
    return true;
}

QJsonObject CGetTemplateRoiMatchPointRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("matchPointXName",matchPointXName);
    obj.insert("matchPointYName",matchPointYName);
    return obj;
}

bool CGetTemplateRoiMatchPointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetTemplateRoiMatchPointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetTemplateRoiMatchPointResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("pointX") && obj["pointX"].isDouble()) pointX = obj["pointX"].toDouble();
    if (obj.contains("pointY") && obj["pointY"].isDouble()) pointY = obj["pointY"].toDouble();
    return true;
}

QJsonObject CGetTemplateRoiMatchPointResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("pointX",pointX);
    obj.insert("pointY",pointY);
    return obj;
}

bool CGetTemplateRoiMatchPointResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetTemplateRoiMatchPointResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
