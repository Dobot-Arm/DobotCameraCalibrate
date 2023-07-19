#include "CalcGetCalibrateResult.h"

bool CCalcGetCalibrateResultRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    return true;
}

QJsonObject CCalcGetCalibrateResultRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    return obj;
}

bool CCalcGetCalibrateResultRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCalcGetCalibrateResultRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CCalcGetCalibrateResultResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("ang0") && obj["ang0"].isDouble()) ang0 = obj["ang0"].toDouble();
    if (obj.contains("ang1") && obj["ang1"].isDouble()) ang1 = obj["ang1"].toDouble();
    if (obj.contains("ang2") && obj["ang2"].isDouble()) ang2 = obj["ang2"].toDouble();
    return true;
}

QJsonObject CCalcGetCalibrateResultResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("ang0",ang0);
    obj.insert("ang1",ang1);
    obj.insert("ang2",ang2);
    return obj;
}

bool CCalcGetCalibrateResultResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("avg") && obj["avg"].isObject())
    {
        avg.fromJson(obj["avg"].toObject());
    }
    if (obj.contains("max") && obj["max"].isObject())
    {
        max.fromJson(obj["max"].toObject());
    }
    return true;
}

QJsonObject CCalcGetCalibrateResultResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("avg", avg.toJsonObject());
    obj.insert("max", max.toJsonObject());
    return obj;
}

bool CCalcGetCalibrateResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCalcGetCalibrateResultResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
