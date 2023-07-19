#ifndef GREYAREARUNRESULT_H
#define GREYAREARUNRESULT_H

#include "BaseRunResult.h"

class GreyAreaRunResult : public BaseRunResult
{
public:
    GreyAreaRunResult():BaseRunResult("greyarea"){}
    virtual ~GreyAreaRunResult(){}

    inline static bool isMine(const QString& strType){return "greyarea"==strType;}

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
    struct ShowArea
    {
        double x = 0;     //SINGLE_show_text_x
        double y = 0;     //SINGLE_show_text_y
        double angle = 0; //SINGLE_show_text_ang
    };
    double area = 0.0; //SINGLE_rst_measure
    double limitDown = 0; //SINGLE_rst_measure_limit_l
    double limitUp = 0; //SINGLE_rst_measure_limit_h
    BoxArea boxArea;
    ShowArea areaShowArea;
    QString frame;
};

#endif // GREYAREARUNRESULT_H
