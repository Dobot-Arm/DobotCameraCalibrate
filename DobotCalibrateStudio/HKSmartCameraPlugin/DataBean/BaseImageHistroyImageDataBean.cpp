#include "BaseImageHistroyImageDataBean.h"

bool CBaseImageHistroyImageDataRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("imageName") && obj["imageName"].isDouble()) imageName = obj["imageName"].toString();
    return true;
}

QJsonObject CBaseImageHistroyImageDataRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("imageName", imageName);
    return obj;
}

bool CBaseImageHistroyImageDataRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CBaseImageHistroyImageDataRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CBaseImageHistroyImageDataResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("frame") && obj["frame"].isString()) frame = obj["frame"].toString();
    return true;
}

QJsonObject CBaseImageHistroyImageDataResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("frame",frame);
    return obj;
}

bool CBaseImageHistroyImageDataResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CBaseImageHistroyImageDataResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
