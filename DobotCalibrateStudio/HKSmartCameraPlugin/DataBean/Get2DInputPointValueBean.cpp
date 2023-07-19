#include "Get2DInputPointValueBean.h"

bool CGet2DInputPointValueRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGet2DInputPointValueRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGet2DInputPointValueRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGet2DInputPointValueRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGet2DInputPointValueResponseBean1::fromJson(const QJsonObject &obj)
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

QJsonObject CGet2DInputPointValueResponseBean1::toJsonObject() const
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

bool CGet2DInputPointValueResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("runPointX") && obj["runPointX"].isObject())
    {
        runPointX.fromJson(obj["runPointX"].toObject());
    }
    if (obj.contains("runPointY") && obj["runPointY"].isObject())
    {
        runPointY.fromJson(obj["runPointY"].toObject());
    }
    if (obj.contains("runPointAngle") && obj["runPointAngle"].isObject())
    {
        runPointAngle.fromJson(obj["runPointAngle"].toObject());
    }
    return true;
}

QJsonObject CGet2DInputPointValueResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("runPointX", runPointX.toJsonObject());
    obj.insert("runPointY", runPointY.toJsonObject());
    obj.insert("runPointAngle", runPointAngle.toJsonObject());
    return obj;
}

bool CGet2DInputPointValueResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGet2DInputPointValueResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
