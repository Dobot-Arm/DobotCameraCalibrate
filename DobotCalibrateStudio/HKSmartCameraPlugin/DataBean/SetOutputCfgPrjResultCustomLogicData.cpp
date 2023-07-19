#include "SetOutputCfgPrjResultCustomLogicData.h"

bool CSetOutputConfigProjectResultCustomLogicDataRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramValue") && obj["paramValue"].isString()) paramValue = obj["paramValue"].toString();
    if (obj.contains("showValueCN") && obj["showValueCN"].isString()) showValueCN = obj["showValueCN"].toString();
    if (obj.contains("showValueEN") && obj["showValueEN"].isString()) showValueEN = obj["showValueEN"].toString();
    return true;
}

QJsonObject CSetOutputConfigProjectResultCustomLogicDataRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramValue",paramValue);
    obj.insert("showValueCN",showValueCN);
    obj.insert("showValueEN",showValueEN);
    return obj;
}

bool CSetOutputConfigProjectResultCustomLogicDataRequestBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
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
            CSetOutputConfigProjectResultCustomLogicDataRequestBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                logicParams.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CSetOutputConfigProjectResultCustomLogicDataRequestBean2::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=logicParams.begin(); itr != logicParams.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("logicalMode", logicalMode);
    obj.insert("logicParams", dataArray);
    return obj;
}

bool CSetOutputConfigProjectResultCustomLogicDataRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetOutputConfigProjectResultCustomLogicDataRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetOutputConfigProjectResultCustomLogicDataResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetOutputConfigProjectResultCustomLogicDataResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetOutputConfigProjectResultCustomLogicDataResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetOutputConfigProjectResultCustomLogicDataResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
