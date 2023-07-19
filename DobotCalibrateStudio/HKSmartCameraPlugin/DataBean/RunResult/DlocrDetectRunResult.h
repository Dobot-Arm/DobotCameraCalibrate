#ifndef DLOCRDETECTRUNRESULT_H
#define DLOCRDETECTRUNRESULT_H

#include "BaseRunResult.h"

class DlocrDetectRunResult : public BaseRunResult
{
public:
    DlocrDetectRunResult():BaseRunResult("dlocrdetect"){}
    virtual ~DlocrDetectRunResult(){}

    inline static bool isMine(const QString& strType){return "dlocrdetect"==strType;}

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
        double x = 0;     //SINGLE_show_text_x,    SINGLE_show_string_x
        double y = 0;     //SINGLE_show_text_y,    SINGLE_show_string_y
        double angle = 0; //SINGLE_show_text_ang,  SINGLE_show_string_angle
    };
    struct CharValues
    {
        bool status = false; //SINGLE_ocr_obj_status
        QString content = ""; //SINGLE_obj_char_info_1
        double score = 0; //SINGLE_obj_char_confidence_1
        BoxArea boxArea;
        ShowArea scoreShowArea;
        ShowArea contentShowArea;
    };

    int charLimitDown = 0; //SINGLE_rst_num_limit_l
    int charLimitUp = 0; //SINGLE_rst_num_limit_h
    QList<CharValues> charValues;
};

#endif // DLOCRDETECTRUNRESULT_H
