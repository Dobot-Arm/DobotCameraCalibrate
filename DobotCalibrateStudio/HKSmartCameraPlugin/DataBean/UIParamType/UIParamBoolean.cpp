#include "UIParamBoolean.h"

bool UIParamBoolean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("success") && obj["success"].isBool()) success = obj["success"].toBool();
    if (obj.contains("errmsg") && obj["errmsg"].isString()) errmsg = obj["errmsg"].toString();
    if (obj.contains("value") && obj["value"].isBool()) value = obj["value"].toBool();
    return true;
}

QJsonObject UIParamBoolean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("success", success);
    obj.insert("errmsg", errmsg);
    obj.insert("value", value);
    return obj;
}
