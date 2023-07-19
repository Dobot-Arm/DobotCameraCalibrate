#ifndef UIPARAMUNKNOW_H
#define UIPARAMUNKNOW_H

#include "UIParamBase.h"

class UIParamUnknow : public UIParamBase
{
public:
    UIParamUnknow():UIParamBase("Unknow"){}
    virtual ~UIParamUnknow(){}

    inline static bool isMine(const QString& strType){return "Unknow"==strType||strType.isEmpty();}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // UIPARAMUNKNOW_H
