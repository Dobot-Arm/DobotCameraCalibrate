#include "GetModuleUIParamValueBean.h"

bool CGetModuleUIParamValueRequestBean0::fromJson(const QJsonObject &obj)
{
    paramName = obj["paramName"].toString();
    paramType = obj["paramType"].toString();
    return true;
}

QJsonObject CGetModuleUIParamValueRequestBean0::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName", paramName);
    obj.insert("paramType", paramType);
    return obj;
}

bool CGetModuleUIParamValueRequestBean::fromJson(const QJsonObject &obj)
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
            CGetModuleUIParamValueRequestBean0 bean;
            if (bean.fromJson(arr.at(i).toObject()))
            {
                parameters.append(bean);
            }
        }
    }
    return true;
}

QJsonObject CGetModuleUIParamValueRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    QJsonArray arr;
    for(int i=0; i<parameters.size(); ++i)
    {
        arr.append(parameters.at(i).toJsonObject());
    }
    obj.insert("parameters", arr);
    return obj;
}

bool CGetModuleUIParamValueRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetModuleUIParamValueRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetModuleUIParamValueResponseBean::fromJson(const QJsonObject &obj)
{
    paramName = obj["paramName"].toString();
    paramType = obj["paramType"].toString();
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

QJsonObject CGetModuleUIParamValueResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName",paramName);
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

bool CGetModuleUIParamValueResponseResult::fromJson(const QJsonObject &obj)
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
            CGetModuleUIParamValueResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetModuleUIParamValueResponseResult::toJsonObject() const
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
