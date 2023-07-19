#ifndef CSTARTVIDEOBEAN_H
#define CSTARTVIDEOBEAN_H

#include "JsonMessage.h"

struct CStartVideoRequestBean : public CJsonMessage
{
    virtual ~CStartVideoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CStartVideoRequestParams : public CJsonMessage
{
public:
    CStartVideoRequestParams(){};
    virtual ~CStartVideoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStartVideoResponseBean : public CJsonMessage
{
    virtual ~CStartVideoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame;
};

class CStartVideoResponseResult : public CJsonMessage
{
public:
    CStartVideoResponseResult(){};
    virtual ~CStartVideoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoResponseBean m_data;
};

#endif // CSTARTVIDEOBEAN_H
