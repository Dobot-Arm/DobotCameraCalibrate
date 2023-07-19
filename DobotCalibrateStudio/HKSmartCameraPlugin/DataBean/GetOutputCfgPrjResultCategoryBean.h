#ifndef GETOUTPUTCONFIGPROJECTRESULTCATEGORY_H
#define GETOUTPUTCONFIGPROJECTRESULTCATEGORY_H

#include "JsonMessage.h"

struct CGetOutputConfigProjectResultCategoryRequestBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCategoryRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetOutputConfigProjectResultCategoryRequestParams : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCategoryRequestParams(){};
    virtual ~CGetOutputConfigProjectResultCategoryRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputConfigProjectResultCategoryRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOutputConfigProjectResultCategoryResponseBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCategoryResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    unsigned int value = 0;
    QList<unsigned int> supportValues;
};

class CGetOutputConfigProjectResultCategoryResponseResult : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCategoryResponseResult(){};
    virtual ~CGetOutputConfigProjectResultCategoryResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputConfigProjectResultCategoryResponseBean m_data;
};

#endif // GETOUTPUTCONFIGPROJECTRESULTCATEGORY_H
