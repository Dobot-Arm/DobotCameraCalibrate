#include "DownloadFileBean.h"

bool CDownloadFileRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    remoteFilePath = obj["remoteFilePath"].toString();
    localFilePath = obj["localFilePath"].toString();

    return true;
}

QJsonObject CDownloadFileRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("remoteFilePath",remoteFilePath);
    obj.insert("localFilePath",localFilePath);
    return obj;
}

bool CDownloadFileRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CDownloadFileRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CDownloadFileResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CDownloadFileResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CDownloadFileResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CDownloadFileResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
