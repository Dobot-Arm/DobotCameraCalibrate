#ifndef SETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H
#define SETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H

#include "JsonMessage.h"

struct CSetOutputConfigProjectResultCustomLogicDataRequestBean : public CJsonMessage
{
    virtual ~CSetOutputConfigProjectResultCustomLogicDataRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramValue;
    QString showValueCN;
    QString showValueEN;
};

struct CSetOutputConfigProjectResultCustomLogicDataRequestBean2 : public CJsonMessage
{
    virtual ~CSetOutputConfigProjectResultCustomLogicDataRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString logicalMode;//运算类型,“1”-全部OK、”2”-任意OK、”3”-全部NG、”4”-任意NG
    QList<CSetOutputConfigProjectResultCustomLogicDataRequestBean> logicParams;
};

class CSetOutputConfigProjectResultCustomLogicDataRequestParams : public CJsonMessage
{
public:
    CSetOutputConfigProjectResultCustomLogicDataRequestParams(){};
    virtual ~CSetOutputConfigProjectResultCustomLogicDataRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetOutputConfigProjectResultCustomLogicDataRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetOutputConfigProjectResultCustomLogicDataResponseBean : public CJsonMessage
{
    virtual ~CSetOutputConfigProjectResultCustomLogicDataResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetOutputConfigProjectResultCustomLogicDataResponseResult : public CJsonMessage
{
public:
    CSetOutputConfigProjectResultCustomLogicDataResponseResult(){};
    virtual ~CSetOutputConfigProjectResultCustomLogicDataResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICDATABEAN_H
