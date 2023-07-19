#ifndef CGETCALIBRATEPOS_H
#define CGETCALIBRATEPOS_H

#include "JsonMessage.h"
#include <QList>

struct CGetCalibratePosRequestBean : public CJsonMessage
{
    virtual ~CGetCalibratePosRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

struct CGetCalibratePosRequestBean2 : public CJsonMessage
{
    virtual ~CGetCalibratePosRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    CGetCalibratePosRequestBean flangleCenter;
    CGetCalibratePosRequestBean robot;
};

class CGetCalibratePosRequestParams : public CJsonMessage
{
public:
    CGetCalibratePosRequestParams(){};
    virtual ~CGetCalibratePosRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCalibratePosRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetCalibratePosResponseBean : public CJsonMessage
{
    virtual ~CGetCalibratePosResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

class CGetCalibratePosResponseResult : public CJsonMessage
{
public:
    CGetCalibratePosResponseResult(){};
    virtual ~CGetCalibratePosResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetCalibratePosResponseBean> m_data;
};

#endif // CGETCALIBRATEPOS_H
