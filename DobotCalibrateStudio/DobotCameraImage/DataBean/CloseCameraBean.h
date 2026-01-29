#ifndef CCLOSECAMERABEAN_H
#define CCLOSECAMERABEAN_H

#include "JsonMessage.h"

struct CCloseCameraRequestBean : public CJsonMessage
{
    virtual ~CCloseCameraRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCloseCameraRequestParams : public CJsonMessage
{
public:
    CCloseCameraRequestParams(){};
    virtual ~CCloseCameraRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCloseCameraRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCloseCameraResponseBean : public CJsonMessage
{
    virtual ~CCloseCameraResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CCloseCameraResponseResult : public CJsonMessage
{
public:
    CCloseCameraResponseResult(){};
    virtual ~CCloseCameraResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // CCLOSECAMERABEAN_H
