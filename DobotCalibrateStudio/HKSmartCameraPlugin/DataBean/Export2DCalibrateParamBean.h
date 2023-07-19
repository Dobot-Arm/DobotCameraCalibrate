#ifndef EXPORT2DCALIBRATEPARAMBEAN_H
#define EXPORT2DCALIBRATEPARAMBEAN_H

#include "JsonMessage.h"

struct CExport2DCalibrateParamRequestBean : public CJsonMessage
{
    virtual ~CExport2DCalibrateParamRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString saveFileFullName;//保存的标定参数文件全路径，例如：E:\test\a.iwcal
};

class CExport2DCalibrateParamRequestParams : public CJsonMessage
{
public:
    CExport2DCalibrateParamRequestParams(){};
    virtual ~CExport2DCalibrateParamRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CExport2DCalibrateParamRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CExport2DCalibrateParamResponseBean : public CJsonMessage
{
    virtual ~CExport2DCalibrateParamResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CExport2DCalibrateParamResponseResult : public CJsonMessage
{
public:
    CExport2DCalibrateParamResponseResult(){};
    virtual ~CExport2DCalibrateParamResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // EXPORT2DCALIBRATEPARAMBEAN_H
