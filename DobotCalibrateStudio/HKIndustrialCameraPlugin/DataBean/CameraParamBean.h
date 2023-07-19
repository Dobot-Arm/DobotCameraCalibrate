#ifndef CAMERAPARAMBEAN_H
#define CAMERAPARAMBEAN_H

#include "JsonMessage.h"
#include <QStringList>
#include <QHash>

struct GetCameraParamRequestBean : public CJsonMessage
{
    virtual ~GetCameraParamRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify;
    QStringList property;
};

class GetCameraParamRequestParams : public CJsonMessage
{
public:
    GetCameraParamRequestParams(){};
    virtual ~GetCameraParamRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetCameraParamRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct GetCameraParamResponseBean : public CJsonMessage
{
    virtual ~GetCameraParamResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int code;
    QString errmsg;
    QJsonValue value;
};

struct GetCameraParamResponseBean2 : public CJsonMessage
{
    virtual ~GetCameraParamResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QHash<QString, GetCameraParamResponseBean> propertyValue;
};

class GetCameraParamResponseResult : public CJsonMessage
{
public:
    GetCameraParamResponseResult(){};
    virtual ~GetCameraParamResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    GetCameraParamResponseBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct SetCameraParamRequestBean : public CJsonMessage
{
    virtual ~SetCameraParamRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QJsonValue value;
};

struct SetCameraParamRequestBean2 : public CJsonMessage
{
    virtual ~SetCameraParamRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify;
    QHash<QString, SetCameraParamRequestBean> propertyValue;
};

class SetCameraParamRequestParams : public CJsonMessage
{
public:
    SetCameraParamRequestParams(){};
    virtual ~SetCameraParamRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    SetCameraParamRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct SetCameraParamResponseBean : public CJsonMessage
{
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int code;
    QString errmsg;
};

struct SetCameraParamResponseBean2 : public CJsonMessage
{
    virtual ~SetCameraParamResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QHash<QString, SetCameraParamResponseBean> propertyValue;
};

class SetCameraParamResponseResult : public CJsonMessage
{
public:
    SetCameraParamResponseResult(){};
    virtual ~SetCameraParamResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    SetCameraParamResponseBean2 m_data;
};
#endif // CAMERAPARAMBEAN_H
