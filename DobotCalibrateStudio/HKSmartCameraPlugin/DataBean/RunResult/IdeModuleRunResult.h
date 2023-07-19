#ifndef IDEMODULERUNRESULT_H
#define IDEMODULERUNRESULT_H

#include "BaseRunResult.h"

class IdeModuleRunResult : public BaseRunResult
{
public:
    IdeModuleRunResult():BaseRunResult("idemodule"){}
    virtual ~IdeModuleRunResult(){}

    inline static bool isMine(const QString& strType){return "idemodule"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct BoxArea
    {
        double centerX = 0; //BOX_code_box_cx
        double centerY = 0; //BOX_code_box_cy
        double width = 0; //BOX_code_box_w
        double height = 0; //BOX_code_box_h
        double angle = 0; //BOX_code_box_ang
    };
    struct ShowArea
    {
        double x = 0;     //SINGLE_show_text_x,    SINGLE_show_string_x
        double y = 0;     //SINGLE_show_text_y,    SINGLE_show_string_y
        double angle = 0; //SINGLE_show_text_ang,  SINGLE_show_string_angle
    };
    struct CodeValues
    {
        bool status = false; //SINGLE_code_status
        QString content = ""; //SINGLE_code_string
        double score = 0; //SINGLE_code_score
        QString type = ""; //SINGLE_code_type
        BoxArea boxArea;
        ShowArea scoreShowArea;
        ShowArea contentShowArea;
    };

    int codeLimitDown = 0; //SINGLE_rst_num_limit_l
    int codeLimitUp = 0; //SINGLE_rst_num_limit_h
    QList<CodeValues> codeValues;
};

#endif // IDEMODULERUNRESULT_H
