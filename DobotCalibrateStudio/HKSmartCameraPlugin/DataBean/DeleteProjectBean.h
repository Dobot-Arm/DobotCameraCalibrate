#ifndef DELETEPROJECTBEAN_H
#define DELETEPROJECTBEAN_H

#include "JsonMessage.h"

struct CDeleteProjectRequestBean : public CJsonMessage
{
    virtual ~CDeleteProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //要删除的方案名称
};

class CDeleteProjectRequestParams : public CJsonMessage
{
public:
    CDeleteProjectRequestParams(){};
    virtual ~CDeleteProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDeleteProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDeleteProjectResponseBean : public CJsonMessage
{
    virtual ~CDeleteProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDeleteProjectResponseResult : public CJsonMessage
{
public:
    CDeleteProjectResponseResult(){};
    virtual ~CDeleteProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DELETEPROJECTBEAN_H
