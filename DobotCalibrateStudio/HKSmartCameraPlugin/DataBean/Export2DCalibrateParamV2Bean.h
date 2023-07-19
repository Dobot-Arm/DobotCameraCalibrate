#ifndef EXPORT2DCALIBRATEPARAMV2BEAN_H
#define EXPORT2DCALIBRATEPARAMV2BEAN_H

#include "JsonMessage.h"

struct CExport2DCalibrateParamV2RequestBean : public CJsonMessage
{
    virtual ~CExport2DCalibrateParamV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CExport2DCalibrateParamV2RequestParams : public CJsonMessage
{
public:
    CExport2DCalibrateParamV2RequestParams(){};
    virtual ~CExport2DCalibrateParamV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CExport2DCalibrateParamV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CExport2DCalibrateParamV2ResponseBean : public CJsonMessage
{
    virtual ~CExport2DCalibrateParamV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString content;
};

class CExport2DCalibrateParamV2ResponseResult : public CJsonMessage
{
public:
    CExport2DCalibrateParamV2ResponseResult(){};
    virtual ~CExport2DCalibrateParamV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CExport2DCalibrateParamV2ResponseBean m_data;
};

#endif // EXPORT2DCALIBRATEPARAMV2BEAN_H
