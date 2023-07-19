#include "StartVideoBean.h"

bool CStartVideoRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CStartVideoRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CStartVideoRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CStartVideoRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CStartVideoResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("frame") && obj["frame"].isString()) frame = obj["frame"].toString();
    return true;
}

QJsonObject CStartVideoResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("frame",frame);
    return obj;
}

bool CStartVideoResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CStartVideoResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
