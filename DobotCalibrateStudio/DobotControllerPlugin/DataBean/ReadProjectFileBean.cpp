#include "ReadProjectFileBean.h"

bool CReadProjectFileRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    projectName = obj["projectName"].toString();
    fileName = obj["fileName"].toString();
    return true;
}

QJsonObject CReadProjectFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("projectName",projectName);
    obj.insert("fileName",fileName);
    return obj;
}

bool CReadProjectFileRequestParams::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CReadProjectFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CReadProjectFileBean::fromJson(const QJsonObject &obj)
{
    content = obj["content"].toString();
    return true;
}

QJsonObject CReadProjectFileBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("content",content);
    return obj;
}

bool CReadProjectFileResponseResult::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CReadProjectFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
