#include "Set2DInputPointValueBean.h"

bool CSet2DInputPointValueRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    return true;
}

QJsonObject CSet2DInputPointValueRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleId", moduleId);
    obj.insert("paramName", paramName);
    return obj;
}

bool CSet2DInputPointValueRequestBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("parameter") && obj["parameter"].isObject())
    {
        parameter.fromJson(obj["parameter"].toObject());
    }
    return true;
}

QJsonObject CSet2DInputPointValueRequestBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("paramName", paramName);
    obj.insert("parameter", parameter.toJsonObject());
    return obj;
}

bool CSet2DInputPointValueRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSet2DInputPointValueRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSet2DInputPointValueResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSet2DInputPointValueResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSet2DInputPointValueResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSet2DInputPointValueResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
