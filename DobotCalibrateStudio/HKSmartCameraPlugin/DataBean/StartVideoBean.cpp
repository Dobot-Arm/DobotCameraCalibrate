#include "StartVideoBean.h"

bool CStartVideoRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("returnFrame") && obj["returnFrame"].isBool()) returnFrame = obj["returnFrame"].toBool();
    if (obj.contains("returnResult") && obj["returnResult"].isBool()) returnResult = obj["returnResult"].toBool();
    return true;
}

QJsonObject CStartVideoRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("returnFrame",returnFrame);
    obj.insert("returnResult",returnResult);
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
    if (obj.contains("width") && obj["width"].isDouble()) width = obj["width"].toInt();
    if (obj.contains("height") && obj["height"].isDouble()) height = obj["height"].toInt();
    if (obj.contains("result") && obj["result"].isObject()) result.fromJson(obj["result"].toObject());
    return true;
}

QJsonObject CStartVideoResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("frame",frame);
    obj.insert("width",width);
    obj.insert("height",height);
    obj.insert("result", result.toJsonObject());
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
