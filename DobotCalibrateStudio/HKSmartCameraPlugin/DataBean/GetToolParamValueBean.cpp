#include "GetToolParamValueBean.h"

bool CGetToolParamValueRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("subModuleStyle") && obj["subModuleStyle"].isDouble()) subModuleStyle = obj["subModuleStyle"].toInt();
    return true;
}

QJsonObject CGetToolParamValueRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("paramName", paramName);
    obj.insert("subModuleStyle", subModuleStyle);
    return obj;
}

bool CGetToolParamValueRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetToolParamValueRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetToolParamValueResponseBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("displayNameCN") && obj["displayNameCN"].isString()) displayNameCN = obj["displayNameCN"].toString();
    if (obj.contains("displayNameEN") && obj["displayNameEN"].isString()) displayNameEN = obj["displayNameEN"].toString();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("paramNameCN") && obj["paramNameCN"].isString()) paramNameCN = obj["paramNameCN"].toString();
    if (obj.contains("paramNameEN") && obj["paramNameEN"].isString()) paramNameEN = obj["paramNameEN"].toString();
    return true;
}

QJsonObject CGetToolParamValueResponseBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("displayNameCN", displayNameCN);
    obj.insert("displayNameEN", displayNameEN);
    obj.insert("paramName", paramName);
    obj.insert("paramNameCN", paramNameCN);
    obj.insert("paramNameEN", paramNameEN);
    return obj;
}

bool CGetToolParamValueResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetToolParamValueResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
