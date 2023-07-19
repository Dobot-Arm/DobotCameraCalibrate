#ifndef UIPARAMBOOLEAN_H
#define UIPARAMBOOLEAN_H

#include "UIParamBase.h"

class UIParamBoolean : public UIParamBase
{
public:
    UIParamBoolean():UIParamBase("Boolean"){}
    virtual ~UIParamBoolean(){}

    inline static bool isMine(const QString& strType){return "Boolean"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
    bool value = false;
};

#endif // UIPARAMBOOLEAN_H
