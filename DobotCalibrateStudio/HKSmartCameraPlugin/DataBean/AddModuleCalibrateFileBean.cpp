#include "AddModuleCalibrateFileBean.h"

bool CAddModuleCalibrateFileRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("fileFullPath") && obj["fileFullPath"].isString()) fileFullPath = obj["fileFullPath"].toString();
    return true;
}

QJsonObject CAddModuleCalibrateFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("fileName", fileName);
    obj.insert("fileFullPath", fileFullPath);
    return obj;
}

bool CAddModuleCalibrateFileRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CAddModuleCalibrateFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CAddModuleCalibrateFileResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAddModuleCalibrateFileResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CAddModuleCalibrateFileResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAddModuleCalibrateFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
