#ifndef IODEVICEOPEN_H
#define IODEVICEOPEN_H

#include "JsonMessage.h"

struct CIODeviceOpenRequestBean : public CJsonMessage
{
    virtual ~CIODeviceOpenRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int port = 0;
};

class CIODeviceOpenRequestParams : public CJsonMessage
{
public:
    CIODeviceOpenRequestParams(){};
    virtual ~CIODeviceOpenRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CIODeviceOpenRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CIODeviceOpenResponseBean : public CJsonMessage
{
    virtual ~CIODeviceOpenResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CIODeviceOpenResponseResult : public CJsonMessage
{
public:
    CIODeviceOpenResponseResult(){};
    virtual ~CIODeviceOpenResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // IODEVICEOPEN_H
