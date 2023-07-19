#ifndef BASERUNRESULT_H
#define BASERUNRESULT_H

#include "JsonMessage.h"
#include <memory>

class BaseRunResult : public CJsonMessage
{
private:
    const QString m_strType="";

public:
    BaseRunResult(QString strType):m_strType(strType){}
    virtual ~BaseRunResult(){}

    inline QString getType() const{return m_strType;}

    static std::shared_ptr<BaseRunResult> createBase(QString strType);
};

#endif // BASERUNRESULT_H
