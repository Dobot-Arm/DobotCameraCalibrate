#include "GetProjectRunResultBean.h"

bool CGetProjectRunResultRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("allModuleName") && obj["allModuleName"].isArray())
    {
        QJsonArray arrStr = obj["allModuleName"].toArray();
        for (int i=0; i<arrStr.size(); ++i)
        {
            QString str = arrStr[i].toString();
            if (!str.isEmpty())
            {
                allModuleName.push_back(str);
            }
        }
    }
    return true;
}

QJsonObject CGetProjectRunResultRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    QJsonArray arrStr;
    for (int i=0; i<allModuleName.size(); ++i)
    {
        arrStr.append(allModuleName[i]);
    }
    obj.insert("allModuleName", arrStr);
    return obj;
}

bool CGetProjectRunResultRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetProjectRunResultRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetProjectRunResultResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("result") && obj["result"].isString()) result = obj["result"].toString();
    if (obj.contains("resultRefCN") && obj["resultRefCN"].isString()) resultRefCN = obj["resultRefCN"].toString();
    if (obj.contains("resultRefEN") && obj["resultRefEN"].isString()) resultRefEN = obj["resultRefEN"].toString();
    if (obj.contains("moduleData") && obj["moduleData"].isObject())
    {
        moduleData = BaseRunResult::createBase(moduleName);
        if (moduleData.get())
        {
            moduleData->fromJson(obj["moduleData"].toObject());
        }
    }
    return true;
}

QJsonObject CGetProjectRunResultResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("result", result);
    obj.insert("resultRefCN", resultRefCN);
    obj.insert("resultRefEN", resultRefEN);
    if (moduleData.get())
    {
        obj.insert("moduleData", moduleData->toJsonObject());
    }
    else
    {
        obj.insert("moduleData", QJsonObject());
    }
    return obj;
}

bool CGetProjectRunResultResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("solutionName") && obj["solutionName"].isString()) solutionName = obj["solutionName"].toString();
    if (obj.contains("totalNumber") && obj["totalNumber"].isDouble()) totalNumber = obj["totalNumber"].toInt();
    if (obj.contains("ngNumber") && obj["ngNumber"].isDouble()) ngNumber = obj["ngNumber"].toInt();
    if (obj.contains("result") && obj["result"].isString()) result = obj["result"].toString();
    QJsonArray arr = obj.value("data").toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        if (arr[i].isObject())
        {
            CGetProjectRunResultResponseBean bean;
            bean.fromJson(arr[i].toObject());
            data.append(bean);
        }
    }
    return true;
}

QJsonObject CGetProjectRunResultResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("solutionName", solutionName);
    obj.insert("totalNumber", totalNumber);
    obj.insert("ngNumber", ngNumber);
    obj.insert("result", result);

    QJsonArray arr;
    for (int i=0; i<data.size(); ++i)
    {
        arr.append(data[i].toJsonObject());
    }
    obj.insert("data", arr);

    return obj;
}

void CGetProjectRunResultResponseBean2::clear()
{
    solutionName = "";
    totalNumber = 0;
    ngNumber = 0;
    result="NG";
    data.clear();
}

bool CGetProjectRunResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetProjectRunResultResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
