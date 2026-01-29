#include "GetModuleCalibrateFileListBean.h"

bool CGetModuleCalibrateFileListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetModuleCalibrateFileListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetModuleCalibrateFileListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetModuleCalibrateFileListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetModuleCalibrateFileListResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("currentFile") && obj["currentFile"].isString()) currentFile = obj["currentFile"].toString();
    if (obj.contains("fileType") && obj["fileType"].isString()) fileType = obj["fileType"].toString();
    if (obj.contains("maxCount") && obj["maxCount"].isDouble()) maxCount = obj["maxCount"].toInt();
    if (obj.contains("fileList") && obj["fileList"].isArray())
    {
        QJsonArray arr = obj["fileList"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            fileList.append(arr.at(i).toString());
        }
    }
    return true;
}

QJsonObject CGetModuleCalibrateFileListResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("currentFile",currentFile);
    obj.insert("fileType",fileType);
    obj.insert("maxCount",maxCount);
    QJsonArray arr;
    for (int i=0; i<fileList.size(); ++i)
    {
        arr.append(fileList.at(i));
    }
    obj.insert("fileList",arr);
    return obj;
}

bool CGetModuleCalibrateFileListResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetModuleCalibrateFileListResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
