#include "FixtureRunResult.h"

bool FixtureRunResult::fromJson(const QJsonObject &obj)
{
    basePointX = obj["basePointX"].toDouble();
    basePointY = obj["basePointY"].toDouble();
    baseAngle = obj["baseAngle"].toDouble();
    runPointX = obj["runPointX"].toDouble();
    runPointY = obj["runPointY"].toDouble();
    runAngle = obj["runAngle"].toDouble();
    return true;
}

QJsonObject FixtureRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("basePointX",basePointX);
    obj.insert("basePointY",basePointY);
    obj.insert("baseAngle",baseAngle);
    obj.insert("runPointX",runPointX);
    obj.insert("runPointY",runPointY);
    obj.insert("runAngle",runAngle);
    return obj;
}
