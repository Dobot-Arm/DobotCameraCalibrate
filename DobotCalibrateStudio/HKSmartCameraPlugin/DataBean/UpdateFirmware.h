#ifndef UPDATEFIRMWARE_H
#define UPDATEFIRMWARE_H

#include "JsonMessage.h"

struct UpdateFirmwareRequestBean : public CJsonMessage
{
    virtual ~UpdateFirmwareRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString file;//固件文件
};

class UpdateFirmwareRequestParams : public CJsonMessage
{
public:
    UpdateFirmwareRequestParams(){};
    virtual ~UpdateFirmwareRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    UpdateFirmwareRequestBean m_data;
};

/*********************************************************************************************************/
struct UpdateFirmwareResponseBean : public CJsonMessage
{
    virtual ~UpdateFirmwareResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class UpdateFirmwareResponseResult : public CJsonMessage
{
public:
    UpdateFirmwareResponseResult(){};
    virtual ~UpdateFirmwareResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct GetUpdateFirmwareProgressRequestBean : public CJsonMessage
{
    virtual ~GetUpdateFirmwareProgressRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class GetUpdateFirmwareProgressRequestParams : public CJsonMessage
{
public:
    GetUpdateFirmwareProgressRequestParams(){};
    virtual ~GetUpdateFirmwareProgressRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetUpdateFirmwareProgressRequestBean m_data;
};
/*********************************************************************************************************/
struct GetUpdateFirmwareProgressResponseBean : public CJsonMessage
{
    virtual ~GetUpdateFirmwareProgressResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int progress = 0;
    bool status = false;
};

class GetUpdateFirmwareProgressResponseResult : public CJsonMessage
{
public:
    GetUpdateFirmwareProgressResponseResult(){};
    virtual ~GetUpdateFirmwareProgressResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetUpdateFirmwareProgressResponseBean m_data;
};
#endif // UPDATEFIRMWARE_H
