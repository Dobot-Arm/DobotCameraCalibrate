#ifndef SETBASEIMAGEFROMPCBEAN_H
#define SETBASEIMAGEFROMPCBEAN_H

#include "JsonMessage.h"

struct CSetBaseImageFromPCRequestBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromPCRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString imageName; //图像名称,有后缀，比如 a.png
    QString fileFullPath; //导入的原始图片全路径
};

class CSetBaseImageFromPCRequestParams : public CJsonMessage
{
public:
    CSetBaseImageFromPCRequestParams(){};
    virtual ~CSetBaseImageFromPCRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetBaseImageFromPCRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetBaseImageFromPCResponseBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromPCResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetBaseImageFromPCResponseResult : public CJsonMessage
{
public:
    CSetBaseImageFromPCResponseResult(){};
    virtual ~CSetBaseImageFromPCResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETBASEIMAGEFROMPCBEAN_H
