#include "ExportProjectDobotBean.h"

bool CExportProjectDobotRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveFile") && obj["saveFile"].isString()) saveFile = obj["saveFile"].toString();
    if (obj.contains("solutionName") && obj["solutionName"].isString()) solutionName = obj["solutionName"].toString();
    content = obj["content"].toString();
    return true;
}

QJsonObject CExportProjectDobotRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveFile", saveFile);
    obj.insert("solutionName", solutionName);
    obj.insert("content", content);
    return obj;
}

bool CExportProjectDobotRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CExportProjectDobotRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CExportProjectDobotResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CExportProjectDobotResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CExportProjectDobotResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CExportProjectDobotResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
