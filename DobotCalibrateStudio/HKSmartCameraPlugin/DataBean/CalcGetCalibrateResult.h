#ifndef CCALCGETCALIBRATERESULT_H
#define CCALCGETCALIBRATERESULT_H

#include "JsonMessage.h"

struct CCalcGetCalibrateResultRequestBean : public CJsonMessage
{
    virtual ~CCalcGetCalibrateResultRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCalcGetCalibrateResultRequestParams : public CJsonMessage
{
public:
    CCalcGetCalibrateResultRequestParams(){};
    virtual ~CCalcGetCalibrateResultRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCalcGetCalibrateResultRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCalcGetCalibrateResultResponseBean : public CJsonMessage
{
    virtual ~CCalcGetCalibrateResultResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double ang0 = 0.0;
    double ang1 = 0.0;
    double ang2 = 0.0;
};

struct CCalcGetCalibrateResultResponseBean2 : public CJsonMessage
{
    virtual ~CCalcGetCalibrateResultResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    CCalcGetCalibrateResultResponseBean avg;
    CCalcGetCalibrateResultResponseBean max;
};

class CCalcGetCalibrateResultResponseResult : public CJsonMessage
{
public:
    CCalcGetCalibrateResultResponseResult(){};
    virtual ~CCalcGetCalibrateResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCalcGetCalibrateResultResponseBean2 m_data;
};
#endif // CCALCGETCALIBRATERESULT_H
