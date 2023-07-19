#ifndef IODEVICEGETLIGHTPARAM_H
#define IODEVICEGETLIGHTPARAM_H

#include "JsonMessage.h"

struct CIODeviceGetLightParamRequestBean : public CJsonMessage
{
    virtual ~CIODeviceGetLightParamRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int port = 0;
    int channel = 0;
};

class CIODeviceGetLightParamRequestParams : public CJsonMessage
{
public:
    CIODeviceGetLightParamRequestParams(){};
    virtual ~CIODeviceGetLightParamRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceGetLightParamRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CIODeviceGetLightParamResponseBean : public CJsonMessage
{
    virtual ~CIODeviceGetLightParamResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int lightValue = 0;
    int duration = 0;
    bool lightState = false;
};

class CIODeviceGetLightParamResponseResult : public CJsonMessage
{
public:
    CIODeviceGetLightParamResponseResult(){};
    virtual ~CIODeviceGetLightParamResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceGetLightParamResponseBean m_data;
};

#endif // IODEVICEGETLIGHTPARAM_H
