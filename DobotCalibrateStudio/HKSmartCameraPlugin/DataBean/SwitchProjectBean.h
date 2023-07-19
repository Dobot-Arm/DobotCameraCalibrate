#ifndef SWITCHPROJECTBEAN_H
#define SWITCHPROJECTBEAN_H

#include "JsonMessage.h"

struct CSwitchProjectRequestBean : public CJsonMessage
{
    virtual ~CSwitchProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //切换的方案名称
};

class CSwitchProjectRequestParams : public CJsonMessage
{
public:
    CSwitchProjectRequestParams(){};
    virtual ~CSwitchProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSwitchProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSwitchProjectResponseBean : public CJsonMessage
{
    virtual ~CSwitchProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSwitchProjectResponseResult : public CJsonMessage
{
public:
    CSwitchProjectResponseResult(){};
    virtual ~CSwitchProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SWITCHPROJECTBEAN_H
