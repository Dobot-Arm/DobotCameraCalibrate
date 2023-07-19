#include "AnnularRoiData.h"

bool AnnularRoiData::fromJson(const QJsonObject &obj)
{
    if (obj.contains("centerX") && obj["centerX"].isDouble()) centerX = obj["centerX"].toDouble();
    if (obj.contains("centerY") && obj["centerY"].isDouble()) centerY = obj["centerY"].toDouble();
    if (obj.contains("inRadius") && obj["inRadius"].isDouble()) inRadius = obj["inRadius"].toDouble();
    if (obj.contains("outRadius") && obj["outRadius"].isDouble()) outRadius = obj["outRadius"].toDouble();
    if (obj.contains("roiEditType") && obj["roiEditType"].isString()) roiEditType = obj["roiEditType"].toString();
    return true;
}

QJsonObject AnnularRoiData::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("centerX", centerX);
    obj.insert("centerY", centerY);
    obj.insert("inRadius", inRadius);
    obj.insert("outRadius", outRadius);
    obj.insert("roiEditType", roiEditType);
    return obj;
}
