#include "GetRoiContourPointsBean.h"

bool CGetRoiContourPointsRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetRoiContourPointsRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetRoiContourPointsRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetRoiContourPointsRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetRoiContourPointsResponseBean::fromJson(const QJsonObject &obj)
{
    QJsonArray arrPoints = obj["points"].toArray();
    for (int i=0; i<arrPoints.size(); ++i)
    {
        if (!arrPoints[i].isObject()) continue;

        QJsonObject objPt = arrPoints[i].toObject();
        CGetRoiContourPointsResponseBean::Point2D pt;
        pt.x = objPt.value("x").toDouble();
        pt.y = objPt.value("y").toDouble();

        points.append(pt);
    }
    return true;
}

QJsonObject CGetRoiContourPointsResponseBean::toJsonObject() const
{
    QJsonArray arr;
    for(auto itr=points.begin(); itr!=points.end(); ++itr)
    {
        QJsonObject objPt;
        objPt.insert("x",itr->x);
        objPt.insert("y",itr->y);
        arr.append(objPt);
    }

    QJsonObject obj;
    obj.insert("points", arr);
    return obj;
}

bool CGetRoiContourPointsResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CGetRoiContourPointsResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
