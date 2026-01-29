#ifndef SPECKLECOUNTRUNRESULT_H
#define SPECKLECOUNTRUNRESULT_H

#include "BaseRunResult.h"

class SpeckleCountRunResult : public BaseRunResult
{
public:
    SpeckleCountRunResult():BaseRunResult("specklecount"){}
    virtual ~SpeckleCountRunResult(){}

    inline static bool isMine(const QString& strType){return "specklecount"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct BoxArea
    {
        double centerX = 0; //BOX_det_box_cx
        double centerY = 0; //BOX_det_box_cy
        double width = 0; //BOX_det_box_w
        double height = 0; //BOX_det_box_h
        double angle = 0; //BOX_det_box_ang
    };
    struct BlobAreaResult
    {
        double centerX = 0; //BOX1_blob_box_cx
        double centerY = 0; //BOX1_blob_box_cy
        double width = 0; //BOX1_blob_box_w
        double height = 0; //BOX1_match_box_h
        double angle = 0; //BOX1_blob_box_ang
        double area = 0; //SINGLE_area
        double centroidX = 0; //POINT_centroid_x
        double centroidY = 0; //POINT_centroid_y
    };

    QList<BoxArea> boxArea;
    QList<BlobAreaResult> blobArea;
    QString frame;
    int width = 0; //图片宽
    int height = 0; //图片高
};

#endif // SPECKLECOUNTRUNRESULT_H
