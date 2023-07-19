#include "EndCalibrateBean.h"

bool CEndCalibrateRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CEndCalibrateRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CEndCalibrateRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CEndCalibrateRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CEndCalibrateResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("pointCount") && obj["pointCount"].isDouble())
    {
        pointCount = obj["pointCount"].toVariant().toInt();
    }
    return true;
}

QJsonObject CEndCalibrateResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("pointCount", pointCount);
    return obj;
}

bool CEndCalibrateResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CEndCalibrateResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
