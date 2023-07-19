#ifndef COPYPROJECTBEAN_H
#define COPYPROJECTBEAN_H

#include "JsonMessage.h"

struct CCopyProjectRequestBean : public CJsonMessage
{
    virtual ~CCopyProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //原方案名称
    QString newSolutionName; //复制后的方案名称
};

class CCopyProjectRequestParams : public CJsonMessage
{
public:
    CCopyProjectRequestParams(){};
    virtual ~CCopyProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCopyProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCopyProjectResponseBean : public CJsonMessage
{
    virtual ~CCopyProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CCopyProjectResponseResult : public CJsonMessage
{
public:
    CCopyProjectResponseResult(){};
    virtual ~CCopyProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // COPYPROJECTBEAN_H
