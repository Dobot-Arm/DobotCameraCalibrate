#include "UIParamCommand.h"

bool UIParamCommand::fromJson(const QJsonObject &obj)
{
    if (obj.contains("success") && obj["success"].isBool()) success = obj["success"].toBool();
    if (obj.contains("errmsg") && obj["errmsg"].isString()) errmsg = obj["errmsg"].toString();
    return true;
}

QJsonObject UIParamCommand::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("success", success);
    obj.insert("errmsg", errmsg);
    return obj;
}
