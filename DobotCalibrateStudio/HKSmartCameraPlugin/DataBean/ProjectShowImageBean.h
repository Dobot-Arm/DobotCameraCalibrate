#ifndef PROJECTSHOWIMAGEBEAN_H
#define PROJECTSHOWIMAGEBEAN_H

#include "JsonMessage.h"

struct CProjectShowImageRequestBean : public CJsonMessage
{
    virtual ~CProjectShowImageRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString baseImageName; //方案图片名
};

class CProjectShowImageRequestParams : public CJsonMessage
{
public:
    CProjectShowImageRequestParams(){};
    virtual ~CProjectShowImageRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CProjectShowImageRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CProjectShowImageResponseBean : public CJsonMessage
{
    virtual ~CProjectShowImageResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame;
};

class CProjectShowImageResponseResult : public CJsonMessage
{
public:
    CProjectShowImageResponseResult(){};
    virtual ~CProjectShowImageResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CProjectShowImageResponseBean m_data;
};

#endif // PROJECTSHOWIMAGEBEAN_H
