#include "GetCameraCalibratePointBean.h"

bool CGetCameraCalibratePointRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetCameraCalibratePointRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetCameraCalibratePointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetCameraCalibratePointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetCameraCalibratePointResponseBean::fromJson(const QJsonObject &obj)
{
    imageX = obj["imageX"].toDouble();
    imageY = obj["imageY"].toDouble();
    physicalX = obj["physicalX"].toDouble();
    physicalY = obj["physicalY"].toDouble();
    angle = obj["angle"].toDouble();
    return true;
}

QJsonObject CGetCameraCalibratePointResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("imageX", imageX);
    obj.insert("imageY", imageY);
    obj.insert("physicalX", physicalX);
    obj.insert("physicalY", physicalY);
    obj.insert("angle", angle);
    return obj;
}

bool CGetCameraCalibratePointResponseBean2::fromJson(const QJsonObject &obj)
{
    QJsonArray arrTrans = obj["transformPoints"].toArray();
    for (int i=0; i<arrTrans.size(); ++i)
    {
        if (arrTrans[i].isObject())
        {
            CGetCameraCalibratePointResponseBean bean;
            bean.fromJson(arrTrans[i].toObject());
            transformPoints.append(bean);
        }
    }
    QJsonArray arrRota = obj["rotaPoints"].toArray();
    for (int i=0; i<arrRota.size(); ++i)
    {
        if (arrRota[i].isObject())
        {
            CGetCameraCalibratePointResponseBean bean;
            bean.fromJson(arrRota[i].toObject());
            rotaPoints.append(bean);
        }
    }
    return true;
}

QJsonObject CGetCameraCalibratePointResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    QJsonArray arrTrans;
    for (int i=0; i<transformPoints.size(); ++i)
    {
        arrTrans.append(transformPoints[i].toJsonObject());
    }
    QJsonArray arrRota;
    for (int i=0; i<rotaPoints.size(); ++i)
    {
        arrRota.append(rotaPoints[i].toJsonObject());
    }
    obj.insert("transformPoints", arrTrans);
    obj.insert("rotaPoints", arrRota);

    return obj;
}

bool CGetCameraCalibratePointResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetCameraCalibratePointResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
