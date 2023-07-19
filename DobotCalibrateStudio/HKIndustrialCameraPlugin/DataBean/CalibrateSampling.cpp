#include "CalibrateSampling.h"

bool CCalibrateSamplingRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("savePath") && obj["savePath"].isString())
    {
        savePath = obj["savePath"].toString();
    }
    if (obj.contains("returnFrame") && obj["returnFrame"].isBool()) returnFrame = obj["returnFrame"].toBool();
    if (obj.contains("index") && obj["index"].isDouble()) index = obj["index"].toInt();
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("rx") && obj["rx"].isDouble()) rx = obj["rx"].toDouble();
    if (obj.contains("ry") && obj["ry"].isDouble()) ry = obj["ry"].toDouble();
    if (obj.contains("rz") && obj["rz"].isDouble()) rz = obj["rz"].toDouble();

    return true;
}

QJsonObject CCalibrateSamplingRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("savePath",savePath);
    obj.insert("returnFrame",returnFrame);
    obj.insert("index",index);
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("rx",rx);
    obj.insert("ry",ry);
    obj.insert("rz",rz);
    return obj;
}

bool CCalibrateSamplingRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CCalibrateSamplingRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CCalibrateSamplingResultResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("frame") && obj["frame"].isString())
    {
        frame = obj["frame"].toString();
    }
    if (obj.contains("fileName") && obj["fileName"].isString())
    {
        fileName = obj["fileName"].toString();
    }
    return true;
}

QJsonObject CCalibrateSamplingResultResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("frame",frame);
    obj.insert("fileName",fileName);
    return obj;
}

bool CCalibrateSamplingResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CCalibrateSamplingResultResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
