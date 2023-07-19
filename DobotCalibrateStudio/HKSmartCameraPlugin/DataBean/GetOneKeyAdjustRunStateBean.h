#ifndef GETONEKEYADJUSTRUNSTATEBEAN_H
#define GETONEKEYADJUSTRUNSTATEBEAN_H

#include "JsonMessage.h"

struct CGetOneKeyAdjustRunStateRequestBean : public CJsonMessage
{
    virtual ~CGetOneKeyAdjustRunStateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetOneKeyAdjustRunStateRequestParams : public CJsonMessage
{
public:
    CGetOneKeyAdjustRunStateRequestParams(){};
    virtual ~CGetOneKeyAdjustRunStateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOneKeyAdjustRunStateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOneKeyAdjustRunStateResponseBean : public CJsonMessage
{
    virtual ~CGetOneKeyAdjustRunStateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int state;
};

class CGetOneKeyAdjustRunStateResponseResult : public CJsonMessage
{
public:
    CGetOneKeyAdjustRunStateResponseResult(){};
    virtual ~CGetOneKeyAdjustRunStateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOneKeyAdjustRunStateResponseBean m_data;
};

#endif // GETONEKEYADJUSTRUNSTATEBEAN_H
