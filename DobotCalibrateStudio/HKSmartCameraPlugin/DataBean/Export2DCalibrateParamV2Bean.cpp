#include "Export2DCalibrateParamV2Bean.h"

bool CExport2DCalibrateParamV2RequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();

    return true;
}

QJsonObject CExport2DCalibrateParamV2RequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName",moduleName);
    obj.insert("moduleId",moduleId);
    return obj;
}

bool CExport2DCalibrateParamV2RequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CExport2DCalibrateParamV2RequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CExport2DCalibrateParamV2ResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("content") && obj["content"].isString()) content = obj["content"].toString();
    return true;
}

QJsonObject CExport2DCalibrateParamV2ResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("content",content);
    return obj;
}

bool CExport2DCalibrateParamV2ResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CExport2DCalibrateParamV2ResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
