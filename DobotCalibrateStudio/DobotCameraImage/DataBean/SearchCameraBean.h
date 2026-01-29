#ifndef CSEARCHCAMERABEAN_H
#define CSEARCHCAMERABEAN_H

#include <QList>
#include "JsonMessage.h"

struct CSearchCameraRequestBean : public CJsonMessage
{
    virtual ~CSearchCameraRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSearchCameraRequestParams : public CJsonMessage
{
public:
    CSearchCameraRequestParams(){};
    virtual ~CSearchCameraRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CNetcardInfoBean : public CJsonMessage
{
    virtual ~CNetcardInfoBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString name;
    QString ip="0.0.0.0";
    QString mac="00:00:00:00:00:00";
    QString subnetmask="0.0.0.0";
    QString gateway="0.0.0.0";
};

struct CSearchCameraResponseBean : public CJsonMessage
{
    virtual ~CSearchCameraResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString ip;
    QString mac;
    QString subnetmask;
    QString gateway;
    QString sn; //相机序列号
    QString manufacturer; //相机厂商
    QString version;
    QString modelname; //相机型号
    bool accessible; //标识相机是否可以被访问连接
    CNetcardInfoBean netcardinfo;//相机插入的那张网卡信息
};
class CSearchCameraResponseResult : public CJsonMessage
{
public:
    CSearchCameraResponseResult(){};
    virtual ~CSearchCameraResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CSearchCameraResponseBean> m_data;
};

#endif // CSEARCHCAMERABEAN_H
