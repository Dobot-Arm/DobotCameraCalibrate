#include "BeginCalibrateBean.h"

bool CBeginCalibrateRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CBeginCalibrateRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CBeginCalibrateRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CBeginCalibrateRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CBeginCalibrateResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CBeginCalibrateResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CBeginCalibrateResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CBeginCalibrateResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
