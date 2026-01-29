#ifndef CSTARTVIDEOIMAGEBEAN_H
#define CSTARTVIDEOIMAGEBEAN_H

#include "JsonMessage.h"

struct CStartVideoImageRequestBean : public CJsonMessage
{
    virtual ~CStartVideoImageRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString saveDir; //保存目录
};

class CStartVideoImageRequestParams : public CJsonMessage
{
public:
    CStartVideoImageRequestParams(){};
    virtual ~CStartVideoImageRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoImageRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStartVideoImageResponseBean : public CJsonMessage
{
    virtual ~CStartVideoImageResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString subFilePath;
    QString solutionName;
};

class CStartVideoImageResponseResult : public CJsonMessage
{
public:
    CStartVideoImageResponseResult(){};
    virtual ~CStartVideoImageResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoImageResponseBean m_data;
};

#endif // CSTARTVIDEOIMAGEBEAN_H
