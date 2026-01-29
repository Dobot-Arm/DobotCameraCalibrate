#include "WriteProjectFileBean.h"

bool CWriteProjectFileRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    projectName = obj["projectName"].toString();
    fileName = obj["fileName"].toString();
    content = obj["content"].toString();
    return true;
}

QJsonObject CWriteProjectFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("projectName",projectName);
    obj.insert("fileName",fileName);
    obj.insert("content",content);
    return obj;
}

bool CWriteProjectFileRequestParams::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CWriteProjectFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CWriteProjectFileBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CWriteProjectFileBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CWriteProjectFileResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CWriteProjectFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
