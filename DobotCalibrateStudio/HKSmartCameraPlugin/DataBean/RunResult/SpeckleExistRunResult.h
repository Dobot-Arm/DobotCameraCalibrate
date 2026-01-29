#ifndef SPECKLEEXISTRUNRESULT_H
#define SPECKLEEXISTRUNRESULT_H

#include "BaseRunResult.h"

class SpeckleExistRunResult : public BaseRunResult
{
public:
    SpeckleExistRunResult():BaseRunResult("speckleexist"){}
    virtual ~SpeckleExistRunResult(){}

    inline static bool isMine(const QString& strType){return "speckleexist"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct BoxArea
    {
        double centerX = 0; //BOX_det_box_cx,BOX1_blob_box_cx
        double centerY = 0; //BOX_det_box_cy,BOX1_blob_box_cy
        double width = 0; //BOX_det_box_w,BOX1_blob_box_w
        double height = 0; //BOX_det_box_h,BOX1_blob_box_h
        double angle = 0; //BOX_det_box_ang,BOX1_blob_box_ang
    };

    BoxArea boxArea;
    BoxArea blobArea;
    double area = 0; //SINGLE_area
    double centroidX = 0; //POINT_centroid_x
    double centroidY = 0; //POINT_centroid_y
    QString frame;
    int width = 0; //图片宽
    int height = 0; //图片高
    double fixtureRunPointX = 0; //FIXTURE_algo_used_run_point_x
    double fixtureRunPointY = 0; //FIXTURE_algo_used_run_point_y
    double fixtureRunAngle = 0; //FIXTURE_algo_used_run_angle
};

#endif // SPECKLEEXISTRUNRESULT_H
