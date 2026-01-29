#ifndef ADDMODULECALIBRATEFILEV2BEAN_H
#define ADDMODULECALIBRATEFILEV2BEAN_H

#include "JsonMessage.h"

struct CAddModuleCalibrateFileV2RequestBean : public CJsonMessage
{
    virtual ~CAddModuleCalibrateFileV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString content;
};

class CAddModuleCalibrateFileV2RequestParams : public CJsonMessage
{
public:
    CAddModuleCalibrateFileV2RequestParams(){};
    virtual ~CAddModuleCalibrateFileV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAddModuleCalibrateFileV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAddModuleCalibrateFileV2ResponseBean : public CJsonMessage
{
    virtual ~CAddModuleCalibrateFileV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAddModuleCalibrateFileV2ResponseResult : public CJsonMessage
{
public:
    CAddModuleCalibrateFileV2ResponseResult(){};
    virtual ~CAddModuleCalibrateFileV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADDMODULECALIBRATEFILEV2BEAN_H
