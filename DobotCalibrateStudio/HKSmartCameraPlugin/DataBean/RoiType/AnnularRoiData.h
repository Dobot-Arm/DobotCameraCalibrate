#ifndef ANNULARROIDATA_H
#define ANNULARROIDATA_H

#include "BaseRoiData.h"

class AnnularRoiData : public BaseRoiData
{
public:
    AnnularRoiData():BaseRoiData("annularRoi"){}
    virtual ~AnnularRoiData(){}

    inline static bool isMine(const QString& strType){return "annularRoi"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double centerX=0.0;
    double centerY=0.0;
    double inRadius=0.0;
    double outRadius=0.0;
    QString roiEditType;
};

#endif // ANNULARROIDATA_H
