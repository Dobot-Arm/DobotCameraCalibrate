#ifndef GETCURRENTPROJECTRUNNINGSTATEBEAN_H
#define GETCURRENTPROJECTRUNNINGSTATEBEAN_H

#include "JsonMessage.h"

struct CGetCurrentProjectRunningStateRequestBean : public CJsonMessage
{
    virtual ~CGetCurrentProjectRunningStateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CGetCurrentProjectRunningStateRequestParams : public CJsonMessage
{
public:
    CGetCurrentProjectRunningStateRequestParams(){};
    virtual ~CGetCurrentProjectRunningStateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCurrentProjectRunningStateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetCurrentProjectRunningStateResponseBean : public CJsonMessage
{
    virtual ~CGetCurrentProjectRunningStateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool state;//true is running，false is no running
};

class CGetCurrentProjectRunningStateResponseResult : public CJsonMessage
{
public:
    CGetCurrentProjectRunningStateResponseResult(){};
    virtual ~CGetCurrentProjectRunningStateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCurrentProjectRunningStateResponseBean m_data;
};

#endif // GETCURRENTPROJECTRUNNINGSTATEBEAN_H
