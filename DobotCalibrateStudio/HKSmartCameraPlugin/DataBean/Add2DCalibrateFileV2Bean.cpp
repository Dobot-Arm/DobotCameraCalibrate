#include "Add2DCalibrateFileV2Bean.h"

bool CAdd2DCalibrateFileV2RequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("content") && obj["content"].isString()) content = obj["content"].toString();
    return true;
}

QJsonObject CAdd2DCalibrateFileV2RequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("fileName", fileName);
    obj.insert("content", content);
    return obj;
}

bool CAdd2DCalibrateFileV2RequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CAdd2DCalibrateFileV2RequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CAdd2DCalibrateFileV2ResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAdd2DCalibrateFileV2ResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CAdd2DCalibrateFileV2ResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CAdd2DCalibrateFileV2ResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
