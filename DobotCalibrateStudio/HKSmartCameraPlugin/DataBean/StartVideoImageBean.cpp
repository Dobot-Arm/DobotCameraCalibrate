#include "StartVideoImageBean.h"

bool CStartVideoImageRequestBean::fromJson(const QJsonObject &obj)
{
    identify = obj["identify"].toString();
    saveDir = obj["saveDir"].toString();
    return true;
}

QJsonObject CStartVideoImageRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDir", saveDir);
    return obj;
}

bool CStartVideoImageRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CStartVideoImageRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CStartVideoImageResponseBean::fromJson(const QJsonObject &obj)
{
    subFilePath = obj["subFilePath"].toString();
    solutionName = obj["solutionName"].toString();
    return true;
}

QJsonObject CStartVideoImageResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("subFilePath",subFilePath);
    obj.insert("solutionName", solutionName);
    return obj;
}

bool CStartVideoImageResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CStartVideoImageResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
