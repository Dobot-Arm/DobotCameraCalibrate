#ifndef MACAPRILTAGRUNRESULT_H
#define MACAPRILTAGRUNRESULT_H

#include "BaseRunResult.h"

class MacapriltagRunResult : public BaseRunResult
{
public:
    MacapriltagRunResult():BaseRunResult("macapriltag"){}
    virtual ~MacapriltagRunResult(){}

    inline static bool isMine(const QString& strType){return "macapriltag"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
    int id = -1;
};

#endif // MACAPRILTAGRUNRESULT_H
