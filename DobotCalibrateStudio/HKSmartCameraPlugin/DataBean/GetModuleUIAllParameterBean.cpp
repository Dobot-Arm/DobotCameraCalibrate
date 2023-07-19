#include "GetModuleUIAllParameterBean.h"

bool CGetModuleUIAllParameterRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("parameters") && obj["parameters"].isArray())
    {
        QJsonArray arr = obj["parameters"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            QString str = arr.at(i).toString();
            if (!str.isEmpty())
            {
                parameters.append(str);
            }
        }
    }
    return true;
}

QJsonObject CGetModuleUIAllParameterRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    QJsonArray arr;
    for(int i=0; i<parameters.size(); ++i)
    {
        arr.append(parameters.at(i));
    }
    obj.insert("parameters", arr);
    return obj;
}

bool CGetModuleUIAllParameterRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetModuleUIAllParameterRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetModuleUIAllParameterResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("visible") && obj["visible"].isBool()) visible = obj["visible"].toBool();
    if (obj.contains("displayNameCN") && obj["displayNameCN"].isString()) displayNameCN = obj["displayNameCN"].toString();
    if (obj.contains("displayNameEN") && obj["displayNameEN"].isString()) displayNameEN = obj["displayNameEN"].toString();
    if (obj.contains("paramType") && obj["paramType"].isString()) paramType = obj["paramType"].toString();
    if (obj.contains("parameters") && obj["parameters"].isObject())
    {
        parameters = UIParamBase::createBase(paramType);
        if (parameters.get())
        {
            parameters->fromJson(obj["parameters"].toObject());
        }
    }
    return true;
}

QJsonObject CGetModuleUIAllParameterResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName",paramName);
    obj.insert("visible",visible);
    obj.insert("displayNameCN",displayNameCN);
    obj.insert("displayNameEN",displayNameEN);
    obj.insert("paramType",paramType);
    if (parameters.get())
    {
        obj.insert("parameters",parameters->toJsonObject());
    }
    else
    {
        obj.insert("parameters",QJsonObject());
    }
    return obj;
}

bool CGetModuleUIAllParameterResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CGetModuleUIAllParameterResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetModuleUIAllParameterResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}
