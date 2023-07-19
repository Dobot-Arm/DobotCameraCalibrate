#ifndef BASEIMAGEHISTROYIMAGEDATABEAN_H
#define BASEIMAGEHISTROYIMAGEDATABEAN_H

#include "JsonMessage.h"

struct CBaseImageHistroyImageDataRequestBean : public CJsonMessage
{
    virtual ~CBaseImageHistroyImageDataRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString imageName; //图像名称
};

class CBaseImageHistroyImageDataRequestParams : public CJsonMessage
{
public:
    CBaseImageHistroyImageDataRequestParams(){};
    virtual ~CBaseImageHistroyImageDataRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CBaseImageHistroyImageDataRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CBaseImageHistroyImageDataResponseBean : public CJsonMessage
{
    virtual ~CBaseImageHistroyImageDataResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame;
};

class CBaseImageHistroyImageDataResponseResult : public CJsonMessage
{
public:
    CBaseImageHistroyImageDataResponseResult(){};
    virtual ~CBaseImageHistroyImageDataResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CBaseImageHistroyImageDataResponseBean m_data;
};

#endif // BASEIMAGEHISTROYIMAGEDATABEAN_H
