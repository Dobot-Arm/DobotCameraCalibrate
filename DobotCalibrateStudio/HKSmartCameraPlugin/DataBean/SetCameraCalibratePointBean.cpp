#include "SetCameraCalibratePointBean.h"

bool CSetCameraCalibratePointRequestBean::fromJson(const QJsonObject &obj)
{
    imageX = obj["imageX"].toDouble();
    imageY = obj["imageY"].toDouble();
    physicalX = obj["physicalX"].toDouble();
    physicalY = obj["physicalY"].toDouble();
    angle = obj["angle"].toDouble();
    return true;
}

QJsonObject CSetCameraCalibratePointRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("imageX", imageX);
    obj.insert("imageY", imageY);
    obj.insert("physicalX", physicalX);
    obj.insert("physicalY", physicalY);
    obj.insert("angle", angle);
    return obj;
}


bool CSetCameraCalibratePointRequestBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    QJsonArray arrTrans = obj["transformPoints"].toArray();
    for (int i=0; i<arrTrans.size(); ++i)
    {
        if (arrTrans[i].isObject())
        {
            CSetCameraCalibratePointRequestBean bean;
            bean.fromJson(arrTrans[i].toObject());
            transformPoints.append(bean);
        }
    }
    QJsonArray arrRota = obj["rotaPoints"].toArray();
    for (int i=0; i<arrRota.size(); ++i)
    {
        if (arrRota[i].isObject())
        {
            CSetCameraCalibratePointRequestBean bean;
            bean.fromJson(arrRota[i].toObject());
            rotaPoints.append(bean);
        }
    }
    return true;
}

QJsonObject CSetCameraCalibratePointRequestBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);

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

bool CSetCameraCalibratePointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CSetCameraCalibratePointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CSetCameraCalibratePointResponseBean::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetCameraCalibratePointResponseBean::toJsonObject() const
{
    QJsonObject obj;
    return obj;
}

bool CSetCameraCalibratePointResponseResult::fromJson(const QJsonObject &obj)
{
    Q_UNUSED(obj)
    return true;
}

QJsonObject CSetCameraCalibratePointResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", QJsonValue());
    return obj;
}

