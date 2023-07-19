#ifndef SETCAMERAPWDBEAN_H
#define SETCAMERAPWDBEAN_H

#include "JsonMessage.h"

struct CSetCameraPwdRequestBean : public CJsonMessage
{
    virtual ~CSetCameraPwdRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString oldPassword; //旧密码
    QString newPassword; //新密码
};

class CSetCameraPwdRequestParams : public CJsonMessage
{
public:
    CSetCameraPwdRequestParams(){};
    virtual ~CSetCameraPwdRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetCameraPwdRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetCameraPwdResponseBean : public CJsonMessage
{
    virtual ~CSetCameraPwdResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetCameraPwdResponseResult : public CJsonMessage
{
public:
    CSetCameraPwdResponseResult(){};
    virtual ~CSetCameraPwdResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETCAMERAPWDBEAN_H
