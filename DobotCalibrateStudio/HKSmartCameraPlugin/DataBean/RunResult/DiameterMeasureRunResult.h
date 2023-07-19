#ifndef DIAMETERMEASURERUNRESULT_H
#define DIAMETERMEASURERUNRESULT_H

#include "BaseRunResult.h"

class DiameterMeasureRunResult : public BaseRunResult
{
public:
    DiameterMeasureRunResult():BaseRunResult("diametermeasure"){}
    virtual ~DiameterMeasureRunResult(){}

    inline static bool isMine(const QString& strType){return "diametermeasure"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct EdgePoint
    {
        double x = 0;     //SINGLE_show_text_x,    SINGLE_show_string_x
        double y = 0;     //SINGLE_show_text_y,    SINGLE_show_string_y
    };
    double centerX = 0;
    double centerY = 0;
    double diameter = 0;
    double limitDown = 0;
    double limitUp = 0;
    QList<EdgePoint> okPoints;
    QList<EdgePoint> ngPoints;
};

#endif // DIAMETERMEASURERUNRESULT_H
