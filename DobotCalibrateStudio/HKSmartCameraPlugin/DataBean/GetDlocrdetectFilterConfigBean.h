#ifndef GETDLOCRDETECTFILTERCONFIGBEAN_H
#define GETDLOCRDETECTFILTERCONFIGBEAN_H

#include "JsonMessage.h"

struct CGetDlocrdetectFilterConfigRequestBean : public CJsonMessage
{
    virtual ~CGetDlocrdetectFilterConfigRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetDlocrdetectFilterConfigRequestParams : public CJsonMessage
{
public:
    CGetDlocrdetectFilterConfigRequestParams(){};
    virtual ~CGetDlocrdetectFilterConfigRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetDlocrdetectFilterConfigRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetDlocrdetectFilterConfigResponseBean : public CJsonMessage
{
    virtual ~CGetDlocrdetectFilterConfigResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString key;
    QString value;
};

class CGetDlocrdetectFilterConfigResponseResult : public CJsonMessage
{
public:
    CGetDlocrdetectFilterConfigResponseResult(){};
    virtual ~CGetDlocrdetectFilterConfigResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetDlocrdetectFilterConfigResponseBean> m_data;
};

#endif // GETDLOCRDETECTFILTERCONFIGBEAN_H
