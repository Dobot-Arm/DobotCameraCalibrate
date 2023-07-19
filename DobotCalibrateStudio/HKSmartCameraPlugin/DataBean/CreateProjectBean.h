#ifndef CREATEPROJECTBEAN_H
#define CREATEPROJECTBEAN_H

#include "JsonMessage.h"

struct CCreateProjectRequestBean : public CJsonMessage
{
    virtual ~CCreateProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCreateProjectRequestParams : public CJsonMessage
{
public:
    CCreateProjectRequestParams(){};
    virtual ~CCreateProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCreateProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCreateProjectResponseBean : public CJsonMessage
{
    virtual ~CCreateProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CCreateProjectResponseResult : public CJsonMessage
{
public:
    CCreateProjectResponseResult(){};
    virtual ~CCreateProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};


#endif // CREATEPROJECTBEAN_H
