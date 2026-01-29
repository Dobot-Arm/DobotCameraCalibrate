#include "AddModuleCalibrateFileV2Bean.h"

bool CAddModuleCalibrateFileV2RequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("content") && obj["content"].isString()) content = obj["content"].toString();
    return true;
}

QJsonObject CAddModuleCalibrateFileV2RequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("fileName", fileName);
    obj.insert("content", content);
    return obj;
}

bool CAddModuleCalibrateFileV2RequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CAddModuleCalibrateFileV2RequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CAddModuleCalibrateFileV2ResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAddModuleCalibrateFileV2ResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CAddModuleCalibrateFileV2ResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAddModuleCalibrateFileV2ResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
