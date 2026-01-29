#ifndef FORMATRUNRESULT_H
#define FORMATRUNRESULT_H

#include "BaseRunResult.h"

class FormatRunResult : public BaseRunResult
{
public:
    FormatRunResult():BaseRunResult("format"){}
    virtual ~FormatRunResult(){}

    inline static bool isMine(const QString& strType){return "format"==strType;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString resultValue = "";
};

#endif // FORMATRUNRESULT_H
