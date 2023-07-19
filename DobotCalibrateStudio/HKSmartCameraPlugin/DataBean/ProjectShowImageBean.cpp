#include "ProjectShowImageBean.h"
bool CProjectShowImageRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("baseImageName") && obj["baseImageName"].isString()) baseImageName = obj["baseImageName"].toString();
    return true;
}

QJsonObject CProjectShowImageRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("baseImageName", baseImageName);
    return obj;
}

bool CProjectShowImageRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CProjectShowImageRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CProjectShowImageResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("frame") && obj["frame"].isString()) frame = obj["frame"].toString();
    return true;
}

QJsonObject CProjectShowImageResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("frame",frame);
    return obj;
}

bool CProjectShowImageResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CProjectShowImageResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
