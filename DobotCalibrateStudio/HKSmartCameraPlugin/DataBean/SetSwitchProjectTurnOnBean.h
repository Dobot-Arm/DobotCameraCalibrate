#ifndef SETSWITCHPROJECTTURNONBEAN_H
#define SETSWITCHPROJECTTURNONBEAN_H

#include "JsonMessage.h"

struct CSetSwitchProjectTurnOnRequestBean : public CJsonMessage
{
    virtual ~CSetSwitchProjectTurnOnRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //切换的方案名称
    bool turnOn; //是否通过通信方式切换
};

class CSetSwitchProjectTurnOnRequestParams : public CJsonMessage
{
public:
    CSetSwitchProjectTurnOnRequestParams(){};
    virtual ~CSetSwitchProjectTurnOnRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetSwitchProjectTurnOnRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetSwitchProjectTurnOnResponseBean : public CJsonMessage
{
    virtual ~CSetSwitchProjectTurnOnResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetSwitchProjectTurnOnResponseResult : public CJsonMessage
{
public:
    CSetSwitchProjectTurnOnResponseResult(){};
    virtual ~CSetSwitchProjectTurnOnResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETSWITCHPROJECTTURNONBEAN_H
