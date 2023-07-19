#ifndef STARTVIDEOV2BEAN_H
#define STARTVIDEOV2BEAN_H

#include "JsonMessage.h"

struct CStartVideoV2RequestBean : public CJsonMessage
{
    virtual ~CStartVideoV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CStartVideoV2RequestParams : public CJsonMessage
{
public:
    CStartVideoV2RequestParams(){};
    virtual ~CStartVideoV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStartVideoV2ResponseBean : public CJsonMessage
{
    virtual ~CStartVideoV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CStartVideoV2ResponseResult : public CJsonMessage
{
public:
    CStartVideoV2ResponseResult(){};
    virtual ~CStartVideoV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // STARTVIDEOV2BEAN_H
