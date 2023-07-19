#include "MatchLocateRunResult.h"

bool MatchLocateRunResult::fromJson(const QJsonObject &obj)
{
    precision = obj["precision"].toDouble();
    physicalX = obj["physicalX"].toDouble();
    physicalY = obj["physicalY"].toDouble();
    offsetX = obj["offsetX"].toDouble();
    offsetY = obj["offsetY"].toDouble();
    offsetTheta = obj["offsetTheta"].toDouble();
    return true;
}

QJsonObject MatchLocateRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("precision",precision);
    obj.insert("physicalX",physicalX);
    obj.insert("physicalY",physicalY);
    obj.insert("offsetX",offsetX);
    obj.insert("offsetY",offsetY);
    obj.insert("offsetTheta",offsetTheta);
    return obj;
}
