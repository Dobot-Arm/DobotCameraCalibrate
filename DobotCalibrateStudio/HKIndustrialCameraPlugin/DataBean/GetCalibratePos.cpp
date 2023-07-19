#include "GetCalibratePos.h"

bool CGetCalibratePosRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("rx") && obj["rx"].isDouble()) rx = obj["rx"].toDouble();
    if (obj.contains("ry") && obj["ry"].isDouble()) ry = obj["ry"].toDouble();
    if (obj.contains("rz") && obj["rz"].isDouble()) rz = obj["rz"].toDouble();
    return true;
}

QJsonObject CGetCalibratePosRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("rx",rx);
    obj.insert("ry",ry);
    obj.insert("rz",rz);
    return obj;
}

bool CGetCalibratePosRequestBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("flangleCenter") && obj["flangleCenter"].isObject())
    {
        flangleCenter.fromJson(obj["flangleCenter"].toObject());
    }

    if (obj.contains("robot") && obj["robot"].isObject())
    {
        robot.fromJson(obj["robot"].toObject());
    }

    return true;
}

QJsonObject CGetCalibratePosRequestBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("flangleCenter",flangleCenter.toJsonObject());
    obj.insert("robot",robot.toJsonObject());
    return obj;
}

bool CGetCalibratePosRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CGetCalibratePosRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetCalibratePosResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("rx") && obj["rx"].isDouble()) rx = obj["rx"].toDouble();
    if (obj.contains("ry") && obj["ry"].isDouble()) ry = obj["ry"].toDouble();
    if (obj.contains("rz") && obj["rz"].isDouble()) rz = obj["rz"].toDouble();

    return true;
}

QJsonObject CGetCalibratePosResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("rx",rx);
    obj.insert("ry",ry);
    obj.insert("rz",rz);
    return obj;
}

bool CGetCalibratePosResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CGetCalibratePosResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }
    return true;
}

QJsonObject CGetCalibratePosResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}
