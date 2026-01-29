#ifndef BASEIMAGERUNRESULT_H
#define BASEIMAGERUNRESULT_H

#include "BaseRunResult.h"

class BaseImageRunResult : public BaseRunResult
{
public:
    BaseImageRunResult():BaseRunResult("baseimage"){}
    virtual ~BaseImageRunResult(){}

    inline static bool isMine(const QString& strType){return "baseimage"==strType;}

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

#endif // BASEIMAGERUNRESULT_H
