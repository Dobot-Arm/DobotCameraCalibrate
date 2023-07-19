#include "CopyProjectBean.h"

bool CCopyProjectRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("solutionName") && obj["solutionName"].isString()) solutionName = obj["solutionName"].toString();
    if (obj.contains("newSolutionName") && obj["newSolutionName"].isString()) newSolutionName = obj["newSolutionName"].toString();
    return true;
}

QJsonObject CCopyProjectRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("solutionName", solutionName);
    obj.insert("newSolutionName", newSolutionName);
    return obj;
}

bool CCopyProjectRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCopyProjectRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CCopyProjectResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CCopyProjectResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CCopyProjectResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CCopyProjectResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
