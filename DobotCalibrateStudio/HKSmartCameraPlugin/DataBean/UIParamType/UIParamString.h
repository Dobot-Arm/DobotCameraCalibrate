#ifndef UIPARAMSTRING_H
#define UIPARAMSTRING_H

#include "UIParamBase.h"

class UIParamString : public UIParamBase
{
public:
    UIParamString():UIParamBase("StringReg"){}
    virtual ~UIParamString(){}

    inline static bool isMine(const QString& strType){return "StringReg"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
    QString value;
};

#endif // UIPARAMSTRING_H
