#ifndef IODEVICELIGHTTURNON_H
#define IODEVICELIGHTTURNON_H

#include "JsonMessage.h"

struct CIODeviceLightTurnOnRequestBean : public CJsonMessage
{
    virtual ~CIODeviceLightTurnOnRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int port = 0;
    int channel = 0;
    int lightValue = 0;
    int duration = 0;
};

class CIODeviceLightTurnOnRequestParams : public CJsonMessage
{
public:
    CIODeviceLightTurnOnRequestParams(){};
    virtual ~CIODeviceLightTurnOnRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceLightTurnOnRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CIODeviceLightTurnOnResponseBean : public CJsonMessage
{
    virtual ~CIODeviceLightTurnOnResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CIODeviceLightTurnOnResponseResult : public CJsonMessage
{
public:
    CIODeviceLightTurnOnResponseResult(){};
    virtual ~CIODeviceLightTurnOnResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // IODEVICELIGHTTURNON_H
