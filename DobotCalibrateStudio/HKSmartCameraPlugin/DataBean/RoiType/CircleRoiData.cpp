#include "CircleRoiData.h"

bool CircleRoiData::fromJson(const QJsonObject &obj)
{
    if (obj.contains("centerX") && obj["centerX"].isDouble()) centerX = obj["centerX"].toDouble();
    if (obj.contains("centerY") && obj["centerY"].isDouble()) centerY = obj["centerY"].toDouble();
    if (obj.contains("radius") && obj["radius"].isDouble()) radius = obj["radius"].toDouble();
    if (obj.contains("roiEditType") && obj["roiEditType"].isString()) roiEditType = obj["roiEditType"].toString();
    return true;
}

QJsonObject CircleRoiData::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("centerX", centerX);
    obj.insert("centerY", centerY);
    obj.insert("radius", radius);
    obj.insert("roiEditType", roiEditType);
    return obj;
}
