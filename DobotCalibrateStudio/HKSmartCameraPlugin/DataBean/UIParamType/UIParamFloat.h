#ifndef UIPARAMFLOAT_H
#define UIPARAMFLOAT_H

#include "UIParamBase.h"

class UIParamFloat : public UIParamBase
{
public:
    UIParamFloat():UIParamBase("Float"){}
    virtual ~UIParamFloat(){}

    inline static bool isMine(const QString& strType){return "Float"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
    float value;
    float min;
    float max;
};

#endif // UIPARAMFLOAT_H
