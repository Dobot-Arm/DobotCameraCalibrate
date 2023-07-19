#include "MacapriltagRunResult.h"

bool MacapriltagRunResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("rx") && obj["rx"].isDouble()) rx = obj["rx"].toDouble();
    if (obj.contains("ry") && obj["ry"].isDouble()) ry = obj["ry"].toDouble();
    if (obj.contains("rz") && obj["rz"].isDouble()) rz = obj["rz"].toDouble();
    if (obj.contains("id") && obj["id"].isDouble()) id = obj["id"].toInt();
    return true;
}

QJsonObject MacapriltagRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("rx",rx);
    obj.insert("ry",ry);
    obj.insert("rz",rz);
    obj.insert("id",id);
    return obj;
}
