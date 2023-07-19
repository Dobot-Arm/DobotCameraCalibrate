#ifndef DELETE25DCALIBRATEFILEBEAN_H
#define DELETE25DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CDelete25DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CDelete25DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
};

class CDelete25DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CDelete25DCalibrateFileRequestParams(){};
    virtual ~CDelete25DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDelete25DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDelete25DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CDelete25DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDelete25DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CDelete25DCalibrateFileResponseResult(){};
    virtual ~CDelete25DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DELETE25DCALIBRATEFILEBEAN_H
