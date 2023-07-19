#ifndef POLYGONROIDATA_H
#define POLYGONROIDATA_H

#include "BaseRoiData.h"


class PolygonRoiData : public BaseRoiData
{
public:
    PolygonRoiData():BaseRoiData("polygonRoi"){}
    virtual ~PolygonRoiData(){}

    inline static bool isMine(const QString& strType){return "polygonRoi"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct Point2D
    {
        double pointX;
        double pointY;
    };

    QList<Point2D> points;
    QString roiEditType;
};

#endif // POLYGONROIDATA_H
