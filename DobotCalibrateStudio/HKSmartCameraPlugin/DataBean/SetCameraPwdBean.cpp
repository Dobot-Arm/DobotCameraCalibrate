#include "SetCameraPwdBean.h"

bool CSetCameraPwdRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("oldPassword") && obj["oldPassword"].isString()) oldPassword = obj["oldPassword"].toString();
    if (obj.contains("newPassword") && obj["newPassword"].isString()) newPassword = obj["newPassword"].toString();
    return true;
}

QJsonObject CSetCameraPwdRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", oldPassword);
    obj.insert("newPassword", newPassword);
    return obj;
}

bool CSetCameraPwdRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetCameraPwdRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetCameraPwdResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetCameraPwdResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetCameraPwdResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetCameraPwdResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
