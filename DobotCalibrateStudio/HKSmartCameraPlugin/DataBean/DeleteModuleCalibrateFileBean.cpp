#include "DeleteModuleCalibrateFileBean.h"

bool CDeleteModuleCalibrateFileRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    return true;
}

QJsonObject CDeleteModuleCalibrateFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("fileName", fileName);
    obj.insert("paramName", paramName);
    return obj;
}

bool CDeleteModuleCalibrateFileRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CDeleteModuleCalibrateFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CDeleteModuleCalibrateFileResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CDeleteModuleCalibrateFileResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CDeleteModuleCalibrateFileResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CDeleteModuleCalibrateFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}

