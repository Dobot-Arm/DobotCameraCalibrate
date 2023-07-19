#ifndef UIPARAMBASE_H
#define UIPARAMBASE_H

#include "JsonMessage.h"
#include <memory>

class UIParamBase : public CJsonMessage
{
private:
    const QString m_strType="Unknow";//Boolean Integer Float Enumeration StringReg Command

public:
    UIParamBase(QString strType):m_strType(strType){}
    virtual ~UIParamBase(){}

    inline QString getType() const{return m_strType;}

    static std::shared_ptr<UIParamBase> createBase(QString strType);
};

#endif // UIPARAMBASE_H
