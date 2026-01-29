#include "FormatRunResult.h"

bool FormatRunResult::fromJson(const QJsonObject &obj)
{
    resultValue = obj["resultValue"].toString();
    return true;
}

QJsonObject FormatRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("resultValue",resultValue);
    return obj;
}
