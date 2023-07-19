#ifndef SETBASEIMAGEFROMCURRENTBEAN_H
#define SETBASEIMAGEFROMCURRENTBEAN_H

#include "JsonMessage.h"

struct CSetBaseImageFromCurrentRequestBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromCurrentRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CSetBaseImageFromCurrentRequestParams : public CJsonMessage
{
public:
    CSetBaseImageFromCurrentRequestParams(){};
    virtual ~CSetBaseImageFromCurrentRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetBaseImageFromCurrentRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetBaseImageFromCurrentResponseBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromCurrentResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetBaseImageFromCurrentResponseResult : public CJsonMessage
{
public:
    CSetBaseImageFromCurrentResponseResult(){};
    virtual ~CSetBaseImageFromCurrentResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETBASEIMAGEFROMCURRENTBEAN_H
