#include "SetToolParamValueBean.h"

bool CSetToolParamValueRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    return true;
}

QJsonObject CSetToolParamValueRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleId", moduleId);
    obj.insert("paramName", paramName);
    return obj;
}

bool CSetToolParamValueRequestBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("subModuleStyle") && obj["subModuleStyle"].isDouble()) subModuleStyle = obj["subModuleStyle"].toInt();
    if (obj.contains("parameter") && obj["parameter"].isObject())
    {
        parameter.fromJson(obj["parameter"].toObject());
    }
    return true;
}

QJsonObject CSetToolParamValueRequestBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("paramName", paramName);
    obj.insert("subModuleStyle", subModuleStyle);
    obj.insert("parameter", parameter.toJsonObject());
    return obj;
}

bool CSetToolParamValueRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetToolParamValueRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetToolParamValueResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetToolParamValueResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetToolParamValueResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetToolParamValueResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
