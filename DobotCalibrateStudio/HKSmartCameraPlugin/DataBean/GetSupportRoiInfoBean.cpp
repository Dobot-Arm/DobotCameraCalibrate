#include "GetSupportRoiInfoBean.h"

bool CGetSupportRoiInfoRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetSupportRoiInfoRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetSupportRoiInfoRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetSupportRoiInfoRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetSupportRoiInfoResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("displayNameCN") && obj["displayNameCN"].isString()) displayNameCN = obj["displayNameCN"].toString();
    if (obj.contains("displayNameEN") && obj["displayNameEN"].isString()) displayNameEN = obj["displayNameEN"].toString();
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("roiFlag") && obj["roiFlag"].isBool()) roiFlag = obj["roiFlag"].toBool();
    if (obj.contains("roiEditType") && obj["roiEditType"].isString()) roiEditType = obj["roiEditType"].toString();
    if (obj.contains("supportRoiType") && obj["supportRoiType"].isArray())
    {
        QJsonArray arr = obj["supportRoiType"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            QString str = arr[i].toString();
            if (!str.isEmpty())
            {
                supportRoiType.append(str);
            }
        }
    }
    if (obj.contains("roiMinCount") && obj["roiMinCount"].isDouble()) roiMinCount = obj["roiMinCount"].toInt();
    if (obj.contains("roiMaxCount") && obj["roiMaxCount"].isDouble()) roiMaxCount = obj["roiFlag"].toInt();
    if (obj.contains("matchPointXName") && obj["matchPointXName"].isString()) matchPointXName = obj["matchPointXName"].toString();
    if (obj.contains("matchPointYName") && obj["matchPointYName"].isString()) matchPointYName = obj["matchPointYName"].toString();
    if (obj.contains("matchPointReset") && obj["matchPointReset"].isString()) matchPointReset = obj["matchPointReset"].toString();
    return true;
}

QJsonObject CGetSupportRoiInfoResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("displayNameCN",displayNameCN);
    obj.insert("displayNameEN",displayNameEN);
    obj.insert("paramName",paramName);
    obj.insert("roiFlag",roiFlag);
    obj.insert("roiEditType",roiEditType);
    obj.insert("roiMinCount",roiMinCount);
    obj.insert("roiMaxCount",roiMaxCount);
    QJsonArray arr;
    for (int i=0; i<supportRoiType.size(); ++i)
    {
        arr.append(supportRoiType[i]);
    }
    obj.insert("supportRoiType",arr);
    obj.insert("matchPointXName",matchPointXName);
    obj.insert("matchPointYName",matchPointYName);
    obj.insert("matchPointReset",matchPointReset);
    return obj;
}

bool CGetSupportRoiInfoResponseResult::fromJson(const QJsonObject &obj)
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
            CGetSupportRoiInfoResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetSupportRoiInfoResponseResult::toJsonObject() const
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
