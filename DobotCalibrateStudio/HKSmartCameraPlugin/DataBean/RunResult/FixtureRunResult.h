#ifndef FIXTURERUNRESULT_H
#define FIXTURERUNRESULT_H

#include "BaseRunResult.h"

class FixtureRunResult : public BaseRunResult
{
public:
    FixtureRunResult():BaseRunResult("fixture"){}
    virtual ~FixtureRunResult(){}

    inline static bool isMine(const QString& strType){return "fixture"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double basePointX = 0;
    double basePointY = 0;
    double baseAngle = 0;
    double runPointX = 0;
    double runPointY = 0;
    double runAngle = 0;
};

#endif // FIXTURERUNRESULT_H
