#ifndef UIPARAMENUMERATION_H
#define UIPARAMENUMERATION_H

#include "UIParamBase.h"
#include <QList>

class UIParamEnumeration : public UIParamBase
{
public:
    UIParamEnumeration():UIParamBase("Enumeration"){}
    virtual ~UIParamEnumeration(){}

    inline static bool isMine(const QString& strType){return "Enumeration"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool success = false;
    QString errmsg;
    unsigned int value = 0;
    QList<unsigned int> supportValues;
};

#endif // UIPARAMENUMERATION_H
