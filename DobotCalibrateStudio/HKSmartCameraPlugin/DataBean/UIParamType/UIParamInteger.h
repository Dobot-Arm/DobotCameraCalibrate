#ifndef UIPARAMINTEGER_H
#define UIPARAMINTEGER_H

#include "UIParamBase.h"

class UIParamInteger : public UIParamBase
{
public:
    UIParamInteger():UIParamBase("Integer"){}
    virtual ~UIParamInteger(){}

    inline static bool isMine(const QString& strType){return "Integer"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
    int64_t value;
    int64_t min;
    int64_t max;
    int64_t inc;
};

#endif // UIPARAMINTEGER_H
