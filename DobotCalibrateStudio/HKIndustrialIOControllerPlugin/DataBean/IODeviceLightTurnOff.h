#ifndef IODEVICELIGHTTURNOFF_H
#define IODEVICELIGHTTURNOFF_H

#include "JsonMessage.h"

struct CIODeviceLightTurnOffRequestBean : public CJsonMessage
{
    virtual ~CIODeviceLightTurnOffRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int port = 0;
    int channel = 0;
};

class CIODeviceLightTurnOffRequestParams : public CJsonMessage
{
public:
    CIODeviceLightTurnOffRequestParams(){};
    virtual ~CIODeviceLightTurnOffRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceLightTurnOffRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CIODeviceLightTurnOffResponseBean : public CJsonMessage
{
    virtual ~CIODeviceLightTurnOffResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CIODeviceLightTurnOffResponseResult : public CJsonMessage
{
public:
    CIODeviceLightTurnOffResponseResult(){};
    virtual ~CIODeviceLightTurnOffResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // IODEVICELIGHTTURNOFF_H
