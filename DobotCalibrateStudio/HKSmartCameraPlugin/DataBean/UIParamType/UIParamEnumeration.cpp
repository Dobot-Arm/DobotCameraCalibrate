#include "UIParamEnumeration.h"

bool UIParamEnumeration::fromJson(const QJsonObject &obj)
{
    if (obj.contains("success") && obj["success"].isBool()) success = obj["success"].toBool();
    if (obj.contains("errmsg") && obj["errmsg"].isString()) errmsg = obj["errmsg"].toString();
    if (obj.contains("value") && obj["value"].isDouble()) value = obj["value"].toInt();
    if (obj.contains("supportValues") && obj["supportValues"].isArray())
    {
        QJsonArray arr = obj["supportValues"].toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            supportValues.append(arr.at(i).toInt());
        }
    }
    return true;
}

QJsonObject UIParamEnumeration::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("success", success);
    obj.insert("errmsg", errmsg);
    obj.insert("value", (int)value);
    QJsonArray arr;
    for(int i=0;i<supportValues.size();++i)
    {
        arr.append((int)supportValues.at(i));
    }
    obj.insert("supportValues", arr);
    return obj;
}
