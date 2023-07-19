#ifndef BOXROIDATA_H
#define BOXROIDATA_H

#include "BaseRoiData.h"

class BoxRoiData : public BaseRoiData
{
public:
    BoxRoiData():BaseRoiData("boxRoi"){}
    virtual ~BoxRoiData(){}

    inline static bool isMine(const QString& strType){return "boxRoi"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double centerX=0.0;
    double centerY=0.0;
    double width=0.0;
    double height=0.0;
    QString roiEditType;
    double angle;
};

#endif // BOXROIDATA_H
