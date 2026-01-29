#include "SetSwitchProjectTurnOnBean.h"

bool CSetSwitchProjectTurnOnRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("solutionName") && obj["solutionName"].isString()) solutionName = obj["solutionName"].toString();
    turnOn = obj["turnOn"].toBool();
    return true;
}

QJsonObject CSetSwitchProjectTurnOnRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("solutionName", solutionName);
    obj.insert("turnOn", turnOn);
    return obj;
}

bool CSetSwitchProjectTurnOnRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetSwitchProjectTurnOnRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetSwitchProjectTurnOnResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetSwitchProjectTurnOnResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetSwitchProjectTurnOnResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetSwitchProjectTurnOnResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
