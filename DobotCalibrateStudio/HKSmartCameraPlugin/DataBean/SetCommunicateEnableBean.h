#ifndef SETSetCommunicateEnableBEAN_H
#define SETSetCommunicateEnableBEAN_H

#include "JsonMessage.h"

struct CSetCommunicateEnableRequestBean : public CJsonMessage
{
    virtual ~CSetCommunicateEnableRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    bool enable;//true表示使能打开通信，false表示使能关闭通信
};

class CSetCommunicateEnableRequestParams : public CJsonMessage
{
public:
    CSetCommunicateEnableRequestParams(){};
    virtual ~CSetCommunicateEnableRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetCommunicateEnableRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetCommunicateEnableResponseBean : public CJsonMessage
{
    virtual ~CSetCommunicateEnableResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetCommunicateEnableResponseResult : public CJsonMessage
{
public:
    CSetCommunicateEnableResponseResult(){};
    virtual ~CSetCommunicateEnableResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETSetCommunicateEnableBEAN_H
