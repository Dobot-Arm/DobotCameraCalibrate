#include "UpdateFirmware.h"

bool UpdateFirmwareRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("file") && obj["file"].isString()) file = obj["file"].toString();
    return true;
}

QJsonObject UpdateFirmwareRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("file", file);
    return obj;
}

bool UpdateFirmwareRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject UpdateFirmwareRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
bool UpdateFirmwareResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject UpdateFirmwareResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool UpdateFirmwareResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject UpdateFirmwareResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool GetUpdateFirmwareProgressRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject GetUpdateFirmwareProgressRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool GetUpdateFirmwareProgressRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject GetUpdateFirmwareProgressRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
bool GetUpdateFirmwareProgressResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("progress") && obj["progress"].isDouble()) progress = obj["progress"].toInt();
    if (obj.contains("status") && obj["status"].isBool()) status = obj["status"].toBool();
    return true;
}

QJsonObject GetUpdateFirmwareProgressResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("progress", progress);
    obj.insert("status", status);
    return obj;
}

bool GetUpdateFirmwareProgressResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject GetUpdateFirmwareProgressResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
