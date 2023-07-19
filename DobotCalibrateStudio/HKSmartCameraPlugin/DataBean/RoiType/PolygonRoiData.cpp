#include "PolygonRoiData.h"

bool PolygonRoiData::fromJson(const QJsonObject &obj)
{
    if (obj.contains("roiEditType") && obj["roiEditType"].isString()) roiEditType = obj["roiEditType"].toString();
    QJsonArray arr = obj["points"].toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        if (!arr[i].isObject()) continue;
        auto objPt = arr[i].toObject();
        if (objPt.contains("pointX") && objPt["pointX"].isDouble() &&
            objPt.contains("pointY") && objPt["pointY"].isDouble())
        {
            Point2D pt;
            pt.pointX = objPt["pointX"].toDouble();
            pt.pointY = objPt["pointY"].toDouble();
            points.append(pt);
        }
    }
    return true;
}

QJsonObject PolygonRoiData::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("roiEditType", roiEditType);
    QJsonArray arr;
    for (int i=0; i<points.size(); ++i)
    {
        QJsonObject objPt;
        objPt.insert("pointX",points[i].pointX);
        objPt.insert("pointY",points[i].pointY);
        arr.append(objPt);
    }
    obj.insert("points", arr);
    return obj;
}
