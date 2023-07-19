#include "GetOutputResultSupportListBean.h"

bool CGetOutputResultSupportListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("filterSubType") && obj["filterSubType"].isString()) filterSubType = obj["filterSubType"].toString();
    return true;
}

QJsonObject CGetOutputResultSupportListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("filterSubType", filterSubType);
    return obj;
}

bool CGetOutputResultSupportListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputResultSupportListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOutputResultSupportListResponseBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("paramType") && obj["paramType"].isString()) paramType = obj["paramType"].toString();
    if (obj.contains("paramNameCN") && obj["paramNameCN"].isString()) paramNameCN = obj["paramNameCN"].toString();
    if (obj.contains("paramNameEN") && obj["paramNameEN"].isString()) paramNameEN = obj["paramNameEN"].toString();
    return true;
}

QJsonObject CGetOutputResultSupportListResponseBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName", paramName);
    obj.insert("paramType", paramType);
    obj.insert("paramNameCN", paramNameCN);
    obj.insert("paramNameEN", paramNameEN);
    return obj;
}

bool CGetOutputResultSupportListResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("displayNameCN") && obj["displayNameCN"].isString()) displayNameCN = obj["displayNameCN"].toString();
    if (obj.contains("displayNameEN") && obj["displayNameEN"].isString()) displayNameEN = obj["displayNameEN"].toString();
    QJsonArray subParamListArr = obj["subParamList"].toArray();
    for (int i=0; i<subParamListArr.size(); ++i)
    {
        if (subParamListArr[i].isObject())
        {
            CGetOutputResultSupportListResponseBean1 bean;
            bean.fromJson(subParamListArr[i].toObject());
            subParamList.append(bean);
        }
    }
    return true;
}

QJsonObject CGetOutputResultSupportListResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("displayNameCN", displayNameCN);
    obj.insert("displayNameEN", displayNameEN);
    QJsonArray subParamListArr;
    for (int i=0; i<subParamList.size(); ++i)
    {
        subParamListArr.append(subParamList[i].toJsonObject());
    }
    obj.insert("subParamList", subParamListArr);
    return obj;
}

bool CGetOutputResultSupportListResponseResult::fromJson(const QJsonObject &obj)
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
            CGetOutputResultSupportListResponseBean2 bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }
    return true;
}

QJsonObject CGetOutputResultSupportListResponseResult::toJsonObject() const
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
