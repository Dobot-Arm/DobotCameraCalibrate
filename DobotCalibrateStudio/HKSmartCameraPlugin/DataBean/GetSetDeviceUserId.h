#ifndef GETSETDEVICEUSERID_H
#define GETSETDEVICEUSERID_H

#include "JsonMessage.h"

struct GetDeviceUserIdRequestBean : public CJsonMessage
{
    virtual ~GetDeviceUserIdRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class GetDeviceUserIdRequestParams : public CJsonMessage
{
public:
    GetDeviceUserIdRequestParams(){};
    virtual ~GetDeviceUserIdRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetDeviceUserIdRequestBean m_data;
};

/*********************************************************************************************************/
struct GetDeviceUserIdResponseBean : public CJsonMessage
{
    virtual ~GetDeviceUserIdResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString value;
};

class GetDeviceUserIdResponseResult : public CJsonMessage
{
public:
    GetDeviceUserIdResponseResult(){};
    virtual ~GetDeviceUserIdResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetDeviceUserIdResponseBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct SetDeviceUserIdRequestBean : public CJsonMessage
{
    virtual ~SetDeviceUserIdRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString value;
};

class SetDeviceUserIdRequestParams : public CJsonMessage
{
public:
    SetDeviceUserIdRequestParams(){};
    virtual ~SetDeviceUserIdRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    SetDeviceUserIdRequestBean m_data;
};

/*********************************************************************************************************/
struct SetDeviceUserIdResponseBean : public CJsonMessage
{
    virtual ~SetDeviceUserIdResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class SetDeviceUserIdResponseResult : public CJsonMessage
{
public:
    SetDeviceUserIdResponseResult(){};
    virtual ~SetDeviceUserIdResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // GETSETDEVICEUSERID_H
