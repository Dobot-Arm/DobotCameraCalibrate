#ifndef ADD25DCALIBRATEFILEBEAN_H
#define ADD25DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CAdd25DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CAdd25DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString fileFullPath;
};

class CAdd25DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CAdd25DCalibrateFileRequestParams(){};
    virtual ~CAdd25DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAdd25DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAdd25DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CAdd25DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAdd25DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CAdd25DCalibrateFileResponseResult(){};
    virtual ~CAdd25DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADD25DCALIBRATEFILEBEAN_H
