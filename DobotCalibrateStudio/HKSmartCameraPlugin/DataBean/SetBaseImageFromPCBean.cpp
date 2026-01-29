#include "SetBaseImageFromPCBean.h"

bool CSetBaseImageFromPCRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("imageName") && obj["imageName"].isString()) imageName = obj["imageName"].toString();
    if (obj.contains("fileFullPath") && obj["fileFullPath"].isString()) fileFullPath = obj["fileFullPath"].toString();
    return true;
}

QJsonObject CSetBaseImageFromPCRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("imageName", imageName);
    obj.insert("fileFullPath", fileFullPath);
    return obj;
}

bool CSetBaseImageFromPCRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetBaseImageFromPCRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetBaseImageFromPCResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetBaseImageFromPCResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetBaseImageFromPCResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetBaseImageFromPCResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
