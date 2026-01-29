#include "ImportProjectDobotBean.h"

bool CImportProjectDobotRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("file") && obj["file"].isString()) file = obj["file"].toString();
    return true;
}

QJsonObject CImportProjectDobotRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("file", file);
    return obj;
}

bool CImportProjectDobotRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CImportProjectDobotRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CImportProjectDobotResponseBean::fromJson(const QJsonObject &obj)
{
    content = obj["content"].toString();
    success = obj["success"].toBool();
    msg = obj["msg"].toString();
    return true;
}

QJsonObject CImportProjectDobotResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("content", content);
    obj.insert("success", success);
    obj.insert("msg", msg);
    return obj;
}

bool CImportProjectDobotResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CImportProjectDobotResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
