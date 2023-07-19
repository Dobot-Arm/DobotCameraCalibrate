#include "ResetTemplateRoiMatchPointBean.h"

bool CResetTemplateRoiMatchPointRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("matchPointReset") && obj["matchPointReset"].isString()) matchPointReset = obj["matchPointReset"].toString();
    return true;
}

QJsonObject CResetTemplateRoiMatchPointRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("matchPointReset",matchPointReset);
    return obj;
}

bool CResetTemplateRoiMatchPointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CResetTemplateRoiMatchPointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CResetTemplateRoiMatchPointResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CResetTemplateRoiMatchPointResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CResetTemplateRoiMatchPointResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CResetTemplateRoiMatchPointResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
