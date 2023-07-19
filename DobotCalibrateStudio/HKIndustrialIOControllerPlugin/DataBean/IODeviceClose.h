#ifndef IODEVICECLOSE_H
#define IODEVICECLOSE_H

#include "JsonMessage.h"

struct CIODeviceCloseRequestBean : public CJsonMessage
{
    virtual ~CIODeviceCloseRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int port = 0;
};

class CIODeviceCloseRequestParams : public CJsonMessage
{
public:
    CIODeviceCloseRequestParams(){};
    virtual ~CIODeviceCloseRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceCloseRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CIODeviceCloseResponseBean : public CJsonMessage
{
    virtual ~CIODeviceCloseResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CIODeviceCloseResponseResult : public CJsonMessage
{
public:
    CIODeviceCloseResponseResult(){};
    virtual ~CIODeviceCloseResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // IODEVICECLOSE_H
