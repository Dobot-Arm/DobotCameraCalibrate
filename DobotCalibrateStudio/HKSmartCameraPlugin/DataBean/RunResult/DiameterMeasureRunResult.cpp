#include "DiameterMeasureRunResult.h"

bool DiameterMeasureRunResult::fromJson(const QJsonObject &obj)
{
    centerX = obj["centerX"].toDouble();
    centerY = obj["centerY"].toDouble();
    diameter = obj["diameter"].toDouble();
    limitDown = obj["limitDown"].toDouble();
    limitUp = obj["limitUp"].toDouble();
    QJsonArray arrOk = obj["okPoints"].toArray();
    for (int i=0; i<arrOk.size(); ++i)
    {
        auto objPoint = arrOk[i].toObject();
        DiameterMeasureRunResult::EdgePoint point;
        point.x = objPoint["x"].toDouble();
        point.y = objPoint["y"].toDouble();
        okPoints.push_back(point);
    }
    QJsonArray arrNg = obj["ngPoints"].toArray();
    for (int i=0; i<arrNg.size(); ++i)
    {
        auto objPoint = arrNg[i].toObject();
        DiameterMeasureRunResult::EdgePoint point;
        point.x = objPoint["x"].toDouble();
        point.y = objPoint["y"].toDouble();
        ngPoints.push_back(point);
    }
    return true;
}

QJsonObject DiameterMeasureRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("centerX",centerX);
    obj.insert("centerY",centerY);
    obj.insert("diameter",diameter);
    obj.insert("limitDown",limitDown);
    obj.insert("limitUp",limitUp);

    QJsonArray arrOk;
    for (int i=0; i<okPoints.size(); ++i)
    {
        QJsonObject objPoint;
        objPoint.insert("x",okPoints[i].x);
        objPoint.insert("y",okPoints[i].y);
        arrOk.append(objPoint);
    }
    obj.insert("okPoints",arrOk);

    QJsonArray arrNg;
    for (int i=0; i<ngPoints.size(); ++i)
    {
        QJsonObject objPoint;
        objPoint.insert("x",ngPoints[i].x);
        objPoint.insert("y",ngPoints[i].y);
        arrNg.append(objPoint);
    }
    obj.insert("ngPoints",arrNg);
    return obj;
}
