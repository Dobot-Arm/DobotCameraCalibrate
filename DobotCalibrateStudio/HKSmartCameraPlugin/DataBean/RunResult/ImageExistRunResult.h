#ifndef IMAGEEXISTRUNRESULT_H
#define IMAGEEXISTRUNRESULT_H

#include "BaseRunResult.h"

class ImageExistRunResult : public BaseRunResult
{
public:
    ImageExistRunResult():BaseRunResult("imageexist"){}
    virtual ~ImageExistRunResult(){}

    inline static bool isMine(const QString& strType){return "imageexist"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct MatchBox
    {
        double centerX = 0;
        double centerY = 0;
        double width = 0;
        double height = 0;
        double angle = 0;
    };
    MatchBox matchBox;
    double matchX= 0;
    double matchY = 0;
    double matchAng = 0;
    double score = 0;
};

#endif // IMAGEEXISTRUNRESULT_H
