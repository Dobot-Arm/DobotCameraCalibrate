#ifndef ALLPROJECTLISTBEAN_H
#define ALLPROJECTLISTBEAN_H

#include "JsonMessage.h"

struct CAllProjectListRequestBean : public CJsonMessage
{
    virtual ~CAllProjectListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
};

class CAllProjectListRequestParams : public CJsonMessage
{
public:
    CAllProjectListRequestParams(){};
    virtual ~CAllProjectListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAllProjectListRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAllProjectListResponseBean : public CJsonMessage
{
    virtual ~CAllProjectListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString name;
    QString createDateTime;
    QString baseImageName; //方案图片名
};

struct CAllProjectListResponseBean2 : public CJsonMessage
{
    virtual ~CAllProjectListResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString name;
    QList<CAllProjectListResponseBean> all;
};

class CAllProjectListResponseResult : public CJsonMessage
{
public:
    CAllProjectListResponseResult(){};
    virtual ~CAllProjectListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAllProjectListResponseBean2 m_data;
};
#endif // ALLPROJECTLISTBEAN_H
