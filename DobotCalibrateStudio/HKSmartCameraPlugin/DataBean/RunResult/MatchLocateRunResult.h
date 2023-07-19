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

    double precision = 0;
    double physicalX = 0;
    double physicalY = 0;
    double offsetX = 0;
    double offsetY = 0;
    double offsetTheta = 0;
};

#endif // MATCHLOCATERUNRESULT_H
