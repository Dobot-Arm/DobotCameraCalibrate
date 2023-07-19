#include "CameraParamBean.h"

bool GetCameraParamRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString())
    {
        identify = obj["identify"].toString();
    }
    if (obj.contains("property") && obj["property"].isArray())
    {
        QJsonArray arr = obj["property"].toArray();
        for(auto itr=arr.begin(); itr!=arr.end(); ++itr)
        {
            if (itr->isString())
            {
                property.push_back(itr->toString());
            }
        }
    }

    return true;
}

QJsonObject GetCameraParamRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify",identify);
    obj.insert("property",QJsonArray::fromStringList(property));
    return obj;
}

bool GetCameraParamRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject GetCameraParamRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool GetCameraParamResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("code") && obj["code"].isDouble()) code = obj["code"].toInt();
    if (obj.contains("errmsg") && obj["errmsg"].isString())
    {
        errmsg = obj["errmsg"].toString();
    }
    if (obj.contains("value")) value = obj["value"];
    return true;
}

QJsonObject GetCameraParamResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("code", code);
    obj.insert("errmsg", errmsg);
    obj.insert("value", value);
    return obj;
}

bool GetCameraParamResponseBean2::fromJson(const QJsonObject &obj)
{
    for(auto itr=obj.begin(); itr!=obj.end(); ++itr)
    {
        if (itr.value().isObject())
        {
            GetCameraParamResponseBean bean;
            bean.fromJson(itr.value().toObject());
            propertyValue.insert(itr.key(), bean);
        }
    }
    return true;
}

QJsonObject GetCameraParamResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    for(auto itr=propertyValue.begin(); itr!=propertyValue.end(); ++itr)
    {
        obj.insert(itr.key(), itr.value().toJsonObject());
    }
    return obj;
}

bool GetCameraParamResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject GetCameraParamResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool SetCameraParamRequestBean::fromJson(const QJsonObject& obj)
{
    if (obj.contains("value")) value = obj["value"];
    return true;
}

QJsonObject SetCameraParamRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("value", value);
    return obj;
}

bool SetCameraParamRequestBean2::fromJson(const QJsonObject& obj)
{
    for(auto itr=obj.begin(); itr!=obj.end(); ++itr)
    {
        if (itr.value().isObject())
        {
            SetCameraParamRequestBean bean;
            bean.fromJson(itr.value().toObject());
            propertyValue.insert(itr.key(), bean);
        }
    }
    return true;
}

QJsonObject SetCameraParamRequestBean2::toJsonObject() const
{
    QJsonObject obj;
    for(auto itr=propertyValue.begin(); itr!=propertyValue.end(); ++itr)
    {
        obj.insert(itr.key(), itr.value().toJsonObject());
    }
    return obj;
}

bool SetCameraParamRequestParams::fromJson(const QJsonObject& obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject SetCameraParamRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool SetCameraParamResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("code") && obj["code"].isDouble()) code = obj["code"].toInt();
    if (obj.contains("errmsg") && obj["errmsg"].isString())
    {
        errmsg = obj["errmsg"].toString();
    }
    return true;
}

QJsonObject SetCameraParamResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("code", code);
    obj.insert("errmsg", errmsg);
    return obj;
}

bool SetCameraParamResponseBean2::fromJson(const QJsonObject &obj)
{
    for(auto itr=obj.begin(); itr!=obj.end(); ++itr)
    {
        if (itr.value().isObject())
        {
            SetCameraParamResponseBean bean;
            bean.fromJson(itr.value().toObject());
            propertyValue.insert(itr.key(), bean);
        }
    }
    return true;
}

QJsonObject SetCameraParamResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    for(auto itr=propertyValue.begin(); itr!=propertyValue.end(); ++itr)
    {
        obj.insert(itr.key(), itr.value().toJsonObject());
    }
    return obj;
}

bool SetCameraParamResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject SetCameraParamResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
