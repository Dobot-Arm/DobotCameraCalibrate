#ifndef UIPARAMCOMMAND_H
#define UIPARAMCOMMAND_H

#include "UIParamBase.h"

class UIParamCommand : public UIParamBase
{
public:
    UIParamCommand():UIParamBase("Command"){}
    virtual ~UIParamCommand(){}

    inline static bool isMine(const QString& strType){return "Command"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
};

#endif // UIPARAMCOMMAND_H
