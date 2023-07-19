#include "Export2DCalibrateParamBean.h"

bool CExport2DCalibrateParamRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("saveFileFullName") && obj["saveFileFullName"].isString()) saveFileFullName = obj["saveFileFullName"].toString();

    return true;
}

QJsonObject CExport2DCalibrateParamRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName",moduleName);
    obj.insert("moduleId",moduleId);
    obj.insert("saveFileFullName",saveFileFullName);
    return obj;
}

bool CExport2DCalibrateParamRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CExport2DCalibrateParamRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CExport2DCalibrateParamResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CExport2DCalibrateParamResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CExport2DCalibrateParamResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CExport2DCalibrateParamResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}
