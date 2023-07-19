#ifndef UNKNOWROIDATA_H
#define UNKNOWROIDATA_H

#include "BaseRoiData.h"

class UnknowRoiData : public BaseRoiData
{
public:
    UnknowRoiData():BaseRoiData("Unknow"){}
    virtual ~UnknowRoiData(){}

    inline static bool isMine(const QString& strType){return "Unknow"==strType||strType.isEmpty();}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // UNKNOWROIDATA_H
