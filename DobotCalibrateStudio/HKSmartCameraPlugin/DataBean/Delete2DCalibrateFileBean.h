#ifndef DELETE2DCALIBRATEFILEBEAN_H
#define DELETE2DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CDelete2DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CDelete2DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
};

class CDelete2DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CDelete2DCalibrateFileRequestParams(){};
    virtual ~CDelete2DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDelete2DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDelete2DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CDelete2DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDelete2DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CDelete2DCalibrateFileResponseResult(){};
    virtual ~CDelete2DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DELETE2DCALIBRATEFILEBEAN_H
