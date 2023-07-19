#ifndef ADD2DCALIBRATEFILEBEAN_H
#define ADD2DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CAdd2DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CAdd2DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString fileFullPath;
};

class CAdd2DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CAdd2DCalibrateFileRequestParams(){};
    virtual ~CAdd2DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAdd2DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAdd2DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CAdd2DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAdd2DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CAdd2DCalibrateFileResponseResult(){};
    virtual ~CAdd2DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADD2DCALIBRATEFILEBEAN_H
