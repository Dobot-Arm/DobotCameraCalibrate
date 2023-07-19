#ifndef CURRENTPROGRESSBEAN_H
#define CURRENTPROGRESSBEAN_H

#include "JsonMessage.h"

struct CCurrentProgressRequestBean : public CJsonMessage
{
    virtual ~CCurrentProgressRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCurrentProgressRequestParams : public CJsonMessage
{
public:
    CCurrentProgressRequestParams(){};
    virtual ~CCurrentProgressRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCurrentProgressRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCurrentProgressResponseBean : public CJsonMessage
{
    virtual ~CCurrentProgressResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int progress = 0;
    bool status = false;
};

class CCurrentProgressResponseResult : public CJsonMessage
{
public:
    CCurrentProgressResponseResult(){};
    virtual ~CCurrentProgressResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCurrentProgressResponseBean m_data;
};
#endif // CURRENTPROGRESSBEAN_H
