#ifndef MATCHCALIBRUNRESULT_H
#define MATCHCALIBRUNRESULT_H

#include "BaseRunResult.h"

class MatchCalibRunResult : public BaseRunResult
{
public:
    MatchCalibRunResult():BaseRunResult("matchcalib"){}
    virtual ~MatchCalibRunResult(){}

    inline static bool isMine(const QString& strType){return "matchcalib"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct BoxArea
    {
        double centerX = 0; //BOX1_match_box_cx
        double centerY = 0; //BOX1_match_box_cy
        double width = 0; //BOX1_match_box_w
        double height = 0; //BOX1_match_box_h
        double angle = 0; //BOX1_match_box_ang
    };
    struct MatchPoint
    {
        double x = 0;     //POINT_match_point_x,
        double y = 0;     //POINT_match_point_y,
    };
    struct OutputPoint
    {
        double imageX = 0.0;
        double imageY = 0.0;
        double physicalX = 0.0;
        double physicalY = 0.0;
        double angle = 0.0;
    };
    double transformDelta = 0;
    double rotationDelta = 0;
    double score = 0; //SINGLE_match_score
    QString progress;
    BoxArea matchBox;
    MatchPoint matchPoint;
    QList<OutputPoint> outputPoints;
};

#endif // MATCHCALIBRUNRESULT_H
