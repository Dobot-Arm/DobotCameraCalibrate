#include "SetModuleUIParameterBean.h"

bool CSetModuleUIParameterRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("paramType") && obj["paramType"].isString()) paramType = obj["paramType"].toString();
    if (obj.contains("paramValue")) paramValue = obj["paramValue"];
    return true;
}

QJsonObject CSetModuleUIParameterRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName", paramName);
    obj.insert("paramType", paramType);
    obj.insert("paramValue", paramValue);
    return obj;
}

bool CSetModuleUIParameterRequestBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("parameter") && obj["parameter"].isArray())
    {
        QJsonArray arr = obj["parameter"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            QJsonObject jso = arr.at(i).toObject();
            CSetModuleUIParameterRequestBean bean;
            bean.paramName = jso.value("paramName").toString();
            bean.paramType = jso.value("paramType").toString();
            bean.paramValue = jso.value("paramValue");
            if (!bean.paramName.isEmpty() && !bean.paramType.isEmpty())
            {
                parameter.insert(bean.paramName, bean);
            }
        }
    }
    return true;
}

QJsonObject CSetModuleUIParameterRequestBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    QJsonArray arr;
    for(auto itr=parameter.begin(); itr!=parameter.end(); ++itr)
    {
        QJsonObject jso;
        jso.insert("paramName", itr.value().paramName);
        jso.insert("paramType", itr.value().paramType);
        jso.insert("paramValue", itr.value().paramValue);
        arr.append(jso);
    }
    obj.insert("parameter", arr);
    return obj;
}

bool CSetModuleUIParameterRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetModuleUIParameterRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetModuleUIParameterResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("success") && obj["success"].isBool()) success = obj["success"].toBool();
    if (obj.contains("errmsg") && obj["errmsg"].isString()) errmsg = obj["errmsg"].toString();
    return true;
}

QJsonObject CSetModuleUIParameterResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName",paramName);
    obj.insert("success",success);
    obj.insert("errmsg",errmsg);
    return obj;
}

bool CSetModuleUIParameterResponseResult::fromJson(const QJsonObject &obj)
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
            CSetModuleUIParameterResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CSetModuleUIParameterResponseResult::toJsonObject() const
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
