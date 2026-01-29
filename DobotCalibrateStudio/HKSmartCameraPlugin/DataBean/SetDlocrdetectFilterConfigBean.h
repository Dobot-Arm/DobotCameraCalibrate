#ifndef SETDLOCRDETECTFILTERCONFIGBEAN_H
#define SETDLOCRDETECTFILTERCONFIGBEAN_H

#include "JsonMessage.h"

struct CSetDlocrdetectFilterConfigRequestBean : public CJsonMessage
{
    virtual ~CSetDlocrdetectFilterConfigRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString key;
    QString value;
};

struct CSetDlocrdetectFilterConfigRequestBean1 : public CJsonMessage
{
    virtual ~CSetDlocrdetectFilterConfigRequestBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QList<CSetDlocrdetectFilterConfigRequestBean> parameter;
};

class CSetDlocrdetectFilterConfigRequestParams : public CJsonMessage
{
public:
    CSetDlocrdetectFilterConfigRequestParams(){};
    virtual ~CSetDlocrdetectFilterConfigRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetDlocrdetectFilterConfigRequestBean1 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetDlocrdetectFilterConfigResponseBean : public CJsonMessage
{
    virtual ~CSetDlocrdetectFilterConfigResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetDlocrdetectFilterConfigResponseResult : public CJsonMessage
{
public:
    CSetDlocrdetectFilterConfigResponseResult(){};
    virtual ~CSetDlocrdetectFilterConfigResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETDLOCRDETECTFILTERCONFIGBEAN_H
