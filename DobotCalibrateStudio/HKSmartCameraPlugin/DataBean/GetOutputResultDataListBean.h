#ifndef GETOUTPUTRESULTDATALISTBEAN_H
#define GETOUTPUTRESULTDATALISTBEAN_H

#include "JsonMessage.h"

struct CGetOutputResultDataListRequestBean : public CJsonMessage
{
    virtual ~CGetOutputResultDataListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetOutputResultDataListRequestParams : public CJsonMessage
{
public:
    CGetOutputResultDataListRequestParams(){};
    virtual ~CGetOutputResultDataListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputResultDataListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOutputResultDataListResponseBean : public CJsonMessage
{
    virtual ~CGetOutputResultDataListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramValue;
    QString showValueCN;
    QString showValueEN;
    QString separator;
};

struct CGetOutputResultDataListResponseBean1 : public CJsonMessage
{
protected:
    bool m_bIsObject = true;
public:
    CGetOutputResultDataListResponseBean1(bool bIsObject=true):m_bIsObject(bIsObject){}
    virtual ~CGetOutputResultDataListResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    bool customEdit=false;
    QString separator;
    QString resultNGCustom;
    QString resultOKCustom;
    //QJsonValue paramData;//使用下列对象表示
    CGetOutputResultDataListResponseBean dataObj;
    QList<CGetOutputResultDataListResponseBean> dataArr;
};

struct CGetOutputResultDataListResponseBean2 : public CJsonMessage
{
    virtual ~CGetOutputResultDataListResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName; //模块名称
    int moduleId; //模块id值
    QList<CGetOutputResultDataListResponseBean1> subParamList;
};

class CGetOutputResultDataListResponseResult : public CJsonMessage
{
public:
    CGetOutputResultDataListResponseResult(){};
    virtual ~CGetOutputResultDataListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputResultDataListResponseBean2 m_data;
};
#endif // GETOUTPUTRESULTDATALISTBEAN_H
