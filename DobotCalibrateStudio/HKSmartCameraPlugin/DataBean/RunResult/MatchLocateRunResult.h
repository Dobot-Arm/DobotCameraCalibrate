#ifndef MATCHLOCATERUNRESULT_H
#define MATCHLOCATERUNRESULT_H

#include "BaseRunResult.h"

class MatchLocateRunResult : public BaseRunResult
{
public:
    MatchLocateRunResult():BaseRunResult("matchlocate"){}
    virtual ~MatchLocateRunResult(){}

    inline static bool isMine(const QString& strType){return "matchlocate"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct DataResult
    {
        double precision = 0; //SINGLE_pixel_scale
        double physicalX = 0; //POINT2_world_point_x
        double physicalY = 0; //POINT2_world_point_y
        double physicalAng = 0; //SINGLE_world_point_angle
        double offsetX = 0; //POINT3_world_point_x_diff
        double offsetY = 0; //POINT3_world_point_y_diff
        double offsetTheta = 0; //SINGLE_world_point_angle_diff
        double matchCenterX = 0; //BOX1_match_box_cx
        double matchCenterY = 0; //BOX1_match_box_cy
        double matchCenterWidth = 0; //BOX1_match_box_w
        double matchCenterHeight = 0; //BOX1_match_box_h
        double matchCenterAng = 0; //BOX1_match_box_ang
    };
    QList<DataResult> data;
};

#endif // MATCHLOCATERUNRESULT_H
