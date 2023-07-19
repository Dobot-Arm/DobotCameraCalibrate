#ifndef CIRCLEROIDATA_H
#define CIRCLEROIDATA_H

#include "BaseRoiData.h"

class CircleRoiData : public BaseRoiData
{
public:
    CircleRoiData():BaseRoiData("circleRoi"){}
    virtual ~CircleRoiData(){}

    inline static bool isMine(const QString& strType){return "circleRoi"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double centerX=0.0;
    double centerY=0.0;
    double radius=0.0;
    QString roiEditType;
};

#endif // CIRCLEROIDATA_H
