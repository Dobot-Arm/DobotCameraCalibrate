#ifndef GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H
#define GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H

#include "JsonMessage.h"

struct CGetOutputConfigProjectResultCustomLogicDataRequestBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCustomLogicDataRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetOutputConfigProjectResultCustomLogicDataRequestParams : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCustomLogicDataRequestParams(){};
    virtual ~CGetOutputConfigProjectResultCustomLogicDataRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputConfigProjectResultCustomLogicDataRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOutputConfigProjectResultCustomLogicDataResponseBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCustomLogicDataResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramValue;
    QString showValueCN;
    QString showValueEN;
};

struct CGetOutputConfigProjectResultCustomLogicDataResponseBean2 : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCustomLogicDataResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString logicalMode;//运算类型,“1”-全部OK、”2”-任意OK、”3”-全部NG、”4”-任意NG
    QList<CGetOutputConfigProjectResultCustomLogicDataResponseBean> logicParams;
};

class CGetOutputConfigProjectResultCustomLogicDataResponseResult : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCustomLogicDataResponseResult(){};
    virtual ~CGetOutputConfigProjectResultCustomLogicDataResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputConfigProjectResultCustomLogicDataResponseBean2 m_data;
};

#endif // GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H
