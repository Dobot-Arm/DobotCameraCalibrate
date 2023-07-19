#ifndef WIDTHMEASURERUNRESULT_H
#define WIDTHMEASURERUNRESULT_H

#include "BaseRunResult.h"

class WidthMeasureRunResult : public BaseRunResult
{
public:
    WidthMeasureRunResult():BaseRunResult("widthmeasure"){}
    virtual ~WidthMeasureRunResult(){}

    inline static bool isMine(const QString& strType){return "widthmeasure"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct MarkLines
    {
        double startX = 0;
        double startY = 0;
        double endX = 0;
        double endY = 0;
        double angle = 0;
    };

    double width = 0;
    double limitDown = 0;
    double limitUp = 0;
    double showTextX= 0;
    double showTextY = 0;
    double showTextAng = 0;
    QList<MarkLines> markLines;
};

#endif // WIDTHMEASURERUNRESULT_H
