#ifndef CNULLDATABEAN_H
#define CNULLDATABEAN_H

#include "JsonMessage.h"

class CNullDataBean : public CJsonMessage
{
public:
    CNullDataBean(){};
    virtual ~CNullDataBean() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // CNULLDATABEAN_H
