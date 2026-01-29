#ifndef IMAGECOUNTRUNRESULT_H
#define IMAGECOUNTRUNRESULT_H

#include "BaseRunResult.h"

class ImageCountRunResult : public BaseRunResult
{
public:
    ImageCountRunResult():BaseRunResult("imagecount"){}
    virtual ~ImageCountRunResult(){}

    inline static bool isMine(const QString& strType){return "imagecount"==strType;}

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
    struct MatchResult
    {
        double centerX = 0; //BOX1_match_box_cx
        double centerY = 0; //BOX1_match_box_cy
        double width = 0; //BOX1_match_box_w
        double height = 0; //BOX1_match_box_h
        double angle = 0; //BOX1_match_box_ang
        double score = 0; //SINGLE_match_score
        double matchX = 0; //POINT_match_point_x
        double matchY = 0; //POINT_match_point_y
    };

    BoxArea boxArea;
    QList<MatchResult> matchResult;
};

#endif // IMAGECOUNTRUNRESULT_H
