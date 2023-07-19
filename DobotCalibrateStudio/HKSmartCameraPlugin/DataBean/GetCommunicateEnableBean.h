#ifndef GETCOMMUNICATEENABLEBEAN_H
#define GETCOMMUNICATEENABLEBEAN_H

#include "JsonMessage.h"

struct CGetCommunicateEnableRequestBean : public CJsonMessage
{
    virtual ~CGetCommunicateEnableRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetCommunicateEnableRequestParams : public CJsonMessage
{
public:
    CGetCommunicateEnableRequestParams(){};
    virtual ~CGetCommunicateEnableRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCommunicateEnableRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetCommunicateEnableResponseBean : public CJsonMessage
{
    virtual ~CGetCommunicateEnableResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool enable;
};

class CGetCommunicateEnableResponseResult : public CJsonMessage
{
public:
    CGetCommunicateEnableResponseResult(){};
    virtual ~CGetCommunicateEnableResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCommunicateEnableResponseBean m_data;
};

#endif // GETCOMMUNICATEENABLEBEAN_H
