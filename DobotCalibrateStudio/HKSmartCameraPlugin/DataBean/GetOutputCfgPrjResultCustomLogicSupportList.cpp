#include "GetOutputCfgPrjResultCustomLogicSupportList.h"

bool CGetOutputConfigProjectResultCustomLogicSupportListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicSupportListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetOutputConfigProjectResultCustomLogicSupportListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicSupportListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOutputConfigProjectResultCustomLogicSupportListResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramValue") && obj["paramValue"].isString()) paramValue = obj["paramValue"].toString();
    if (obj.contains("showValueCN") && obj["showValueCN"].isString()) showValueCN = obj["showValueCN"].toString();
    if (obj.contains("showValueEN") && obj["showValueEN"].isString()) showValueEN = obj["showValueEN"].toString();
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicSupportListResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramValue",paramValue);
    obj.insert("showValueCN",showValueCN);
    obj.insert("showValueEN",showValueEN);
    return obj;
}

bool CGetOutputConfigProjectResultCustomLogicSupportListResponseResult::fromJson(const QJsonObject &obj)
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
            CGetOutputConfigProjectResultCustomLogicSupportListResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicSupportListResponseResult::toJsonObject() const
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
