#include "UploadFileBean.h"

bool CUploadFileRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    remoteFilePath = obj["remoteFilePath"].toString();
    localFilePath = obj["localFilePath"].toString();

    return true;
}

QJsonObject CUploadFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("remoteFilePath",remoteFilePath);
    obj.insert("localFilePath",localFilePath);
    return obj;
}

bool CUploadFileRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CUploadFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CUploadFileResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CUploadFileResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CUploadFileResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CUploadFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
