#ifndef BASEROIDATA_H
#define BASEROIDATA_H

#include "JsonMessage.h"
#include <memory>

class BaseRoiData : public CJsonMessage
{
private:
    const QString m_strType="Unknow";

public:
    BaseRoiData(QString strType):m_strType(strType){}
    virtual ~BaseRoiData(){}

    inline QString getType() const{return m_strType;}

    static std::shared_ptr<BaseRoiData> createBase(QString strType);
};

#endif // BASEROIDATA_H
