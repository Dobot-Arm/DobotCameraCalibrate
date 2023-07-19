#include "UIParamInteger.h"

bool UIParamInteger::fromJson(const QJsonObject &obj)
{
    if (obj.contains("success") && obj["success"].isBool()) success = obj["success"].toBool();
    if (obj.contains("errmsg") && obj["errmsg"].isString()) errmsg = obj["errmsg"].toString();
    if (obj.contains("value") && obj["value"].isDouble()) value = obj["value"].toDouble();
    if (obj.contains("min") && obj["min"].isDouble()) min = obj["min"].toDouble();
    if (obj.contains("max") && obj["max"].isDouble()) max = obj["max"].toDouble();
    if (obj.contains("inc") && obj["inc"].isDouble()) inc = obj["inc"].toDouble();
    return true;
}

QJsonObject UIParamInteger::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("success", success);
    obj.insert("errmsg", errmsg);
    obj.insert("value", value);
    obj.insert("min", min);
    obj.insert("max", max);
    obj.insert("inc", inc);
    return obj;
}
