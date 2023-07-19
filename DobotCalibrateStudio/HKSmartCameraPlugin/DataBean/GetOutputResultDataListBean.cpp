#include "GetOutputResultDataListBean.h"

bool CGetOutputResultDataListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetOutputResultDataListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetOutputResultDataListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputResultDataListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetOutputResultDataListResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramValue") && obj["paramValue"].isString()) paramValue = obj["paramValue"].toString();
    if (obj.contains("showValueCN") && obj["showValueCN"].isString()) showValueCN = obj["showValueCN"].toString();
    if (obj.contains("showValueEN") && obj["showValueEN"].isString()) showValueEN = obj["showValueEN"].toString();
    if (obj.contains("separator") && obj["separator"].isString()) separator = obj["separator"].toString();
    return true;
}

QJsonObject CGetOutputResultDataListResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramValue",paramValue);
    obj.insert("showValueCN",showValueCN);
    obj.insert("showValueEN",showValueEN);
    obj.insert("separator",separator);
    return obj;
}

bool CGetOutputResultDataListResponseBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("customEdit") && obj["customEdit"].isBool()) customEdit = obj["customEdit"].toBool();
    if (obj.contains("separator") && obj["separator"].isString()) separator = obj["separator"].toString();
    if (obj.contains("resultNGCustom") && obj["resultNGCustom"].isString()) resultNGCustom = obj["resultNGCustom"].toString();
    if (obj.contains("resultOKCustom") && obj["resultOKCustom"].isString()) resultOKCustom = obj["resultOKCustom"].toString();
    if (obj.contains("paramData") && obj["paramData"].isArray())
    {
        m_bIsObject = false;
        QJsonArray arr = obj["paramData"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CGetOutputResultDataListResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                dataArr.append(bean);
            }
        }
    }
    else
    {
        m_bIsObject = true;
        dataObj.fromJson(obj["paramData"].toObject());
    }
    return true;
}

QJsonObject CGetOutputResultDataListResponseBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("customEdit",customEdit);
    obj.insert("separator",separator);
    obj.insert("resultNGCustom",resultNGCustom);
    obj.insert("resultOKCustom",resultOKCustom);
    if (m_bIsObject)
    {
        obj.insert("paramData",dataObj.toJsonObject());
    }
    else
    {
        QJsonArray dataArray;
        for(auto itr=dataArr.begin(); itr != dataArr.end(); ++itr)
        {
            dataArray.append(itr->toJsonObject());
        }
        obj.insert("paramData",dataArray);
    }
    return obj;
}

bool CGetOutputResultDataListResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("subParamList") && obj["subParamList"].isArray())
    {
        QJsonArray arr = obj["subParamList"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CGetOutputResultDataListResponseBean1 bean;
            if (bean.fromJson(itr->toObject()))
            {
                subParamList.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetOutputResultDataListResponseBean2::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=subParamList.begin(); itr != subParamList.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("subParamList", dataArray);
    return obj;
}

bool CGetOutputResultDataListResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetOutputResultDataListResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
