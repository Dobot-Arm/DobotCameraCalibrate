#include "SetTemplateRoiMatchPointBean.h"

bool CSetTemplateRoiMatchPointRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("matchPointXName") && obj["matchPointXName"].isString()) matchPointXName = obj["matchPointXName"].toString();
    if (obj.contains("pointX") && obj["pointX"].isDouble()) pointX = obj["pointX"].toDouble();
    if (obj.contains("matchPointYName") && obj["matchPointYName"].isString()) matchPointYName = obj["matchPointYName"].toString();
    if (obj.contains("pointY") && obj["pointY"].isDouble()) pointY = obj["pointY"].toDouble();
    return true;
}

QJsonObject CSetTemplateRoiMatchPointRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("matchPointXName",matchPointXName);
    obj.insert("pointX",pointX);
    obj.insert("matchPointYName",matchPointYName);
    obj.insert("pointY",pointY);
    return obj;
}

bool CSetTemplateRoiMatchPointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetTemplateRoiMatchPointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetTemplateRoiMatchPointResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetTemplateRoiMatchPointResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetTemplateRoiMatchPointResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetTemplateRoiMatchPointResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
