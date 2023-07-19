#ifndef SETOUTPUTRESULTDATALISTBEAN_H
#define SETOUTPUTRESULTDATALISTBEAN_H

#include "JsonMessage.h"

struct CSetOutputResultDataListRequestBean : public CJsonMessage
{
    virtual ~CSetOutputResultDataListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString paramName;
    QString paramType;
    QString separator;
};

struct CSetOutputResultDataListRequestBean1 : public CJsonMessage
{
protected:
    bool m_bIsObject = true;
public:
    virtual ~CSetOutputResultDataListRequestBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool isObject(){return m_bIsObject;}

    bool customEdit=false;
    QString separator;
    QString resultNGCustom;
    QString resultOKCustom;
    //QJsonValue paramData;//使用下列对象表示
    CSetOutputResultDataListRequestBean dataObj;
    QList<CSetOutputResultDataListRequestBean> dataArr;
};

struct CSetOutputResultDataListRequestBean2 : public CJsonMessage
{
    virtual ~CSetOutputResultDataListRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QList<CSetOutputResultDataListRequestBean1> subParamList;
};

class CSetOutputResultDataListRequestParams : public CJsonMessage
{
public:
    CSetOutputResultDataListRequestParams(){};
    virtual ~CSetOutputResultDataListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetOutputResultDataListRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetOutputResultDataListResponseBean : public CJsonMessage
{
    virtual ~CSetOutputResultDataListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetOutputResultDataListResponseResult : public CJsonMessage
{
public:
    CSetOutputResultDataListResponseResult(){};
    virtual ~CSetOutputResultDataListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetOutputResultDataListResponseBean m_data;
};
#endif // SETOUTPUTRESULTDATALISTBEAN_H
