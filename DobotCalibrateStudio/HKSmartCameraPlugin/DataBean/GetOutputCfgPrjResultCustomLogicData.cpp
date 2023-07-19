#include "GetOutputCfgPrjResultCustomLogicData.h"

bool CGetOutputConfigProjectResultCustomLogicDataRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicDataRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetOutputConfigProjectResultCustomLogicDataRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicDataRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOutputConfigProjectResultCustomLogicDataResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramValue") && obj["paramValue"].isString()) paramValue = obj["paramValue"].toString();
    if (obj.contains("showValueCN") && obj["showValueCN"].isString()) showValueCN = obj["showValueCN"].toString();
    if (obj.contains("showValueEN") && obj["showValueEN"].isString()) showValueEN = obj["showValueEN"].toString();
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicDataResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramValue",paramValue);
    obj.insert("showValueCN",showValueCN);
    obj.insert("showValueEN",showValueEN);
    return obj;
}

bool CGetOutputConfigProjectResultCustomLogicDataResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("logicalMode") && obj["logicalMode"].isString()) logicalMode = obj["logicalMode"].toString();
    if (obj.contains("logicParams") && obj["logicParams"].isArray())
    {
        QJsonArray arr = obj["logicParams"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CGetOutputConfigProjectResultCustomLogicDataResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                logicParams.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicDataResponseBean2::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=logicParams.begin(); itr != logicParams.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("logicalMode", logicalMode);
    obj.insert("logicParams", dataArray);
    return obj;
}

bool CGetOutputConfigProjectResultCustomLogicDataResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputConfigProjectResultCustomLogicDataResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
