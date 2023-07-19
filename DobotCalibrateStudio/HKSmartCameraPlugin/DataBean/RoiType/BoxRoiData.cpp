#include "BoxRoiData.h"

bool BoxRoiData::fromJson(const QJsonObject &obj)
{
    if (obj.contains("centerX") && obj["centerX"].isDouble()) centerX = obj["centerX"].toDouble();
    if (obj.contains("centerY") && obj["centerY"].isDouble()) centerY = obj["centerY"].toDouble();
    if (obj.contains("width") && obj["width"].isDouble()) width = obj["width"].toDouble();
    if (obj.contains("height") && obj["height"].isDouble()) height = obj["height"].toDouble();
    if (obj.contains("roiEditType") && obj["roiEditType"].isString()) roiEditType = obj["roiEditType"].toString();
    if (obj.contains("angle") && obj["angle"].isDouble()) angle = obj["angle"].toDouble();
    return true;
}

QJsonObject BoxRoiData::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("centerX", centerX);
    obj.insert("centerY", centerY);
    obj.insert("width", width);
    obj.insert("height", height);
    obj.insert("roiEditType", roiEditType);
    obj.insert("angle", angle);
    return obj;
}
