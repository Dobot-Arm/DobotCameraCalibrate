#include "GenerateCalibrateFileV2.h"

bool CGenerateCalibrateFileV2RequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("type") && obj["type"].isString()) type = obj["type"].toString();
    if ("xml" != type || "yml" != type || "json" != type)
    {
        type = "json";
    }
    return true;
}

QJsonObject CGenerateCalibrateFileV2RequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("type", type);
    return obj;
}

bool CGenerateCalibrateFileV2RequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGenerateCalibrateFileV2RequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGenerateCalibrateFileV2ResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("content") && obj["content"].isString()) content = obj["content"].toString();
    return true;
}

QJsonObject CGenerateCalibrateFileV2ResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("content", content);
    return obj;
}

bool CGenerateCalibrateFileV2ResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGenerateCalibrateFileV2ResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

