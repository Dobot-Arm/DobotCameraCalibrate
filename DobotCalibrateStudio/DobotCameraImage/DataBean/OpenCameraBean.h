#ifndef COPENCAMERABEAN_H
#define COPENCAMERABEAN_H

#include "JsonMessage.h"

struct COpenCameraRequestBean : public CJsonMessage
{
    virtual ~COpenCameraRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString password;
};

class COpenCameraRequestParams : public CJsonMessage
{
public:
    COpenCameraRequestParams(){};
    virtual ~COpenCameraRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    COpenCameraRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct COpenCameraResponseBean : public CJsonMessage
{
    virtual ~COpenCameraResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class COpenCameraResponseResult : public CJsonMessage
{
public:
    COpenCameraResponseResult(){};
    virtual ~COpenCameraResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // COPENCAMERABEAN_H
