#ifndef ADD2DCALIBRATEFILEV2BEAN_H
#define ADD2DCALIBRATEFILEV2BEAN_H

#include "JsonMessage.h"

struct CAdd2DCalibrateFileV2RequestBean : public CJsonMessage
{
    virtual ~CAdd2DCalibrateFileV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString content;
};

class CAdd2DCalibrateFileV2RequestParams : public CJsonMessage
{
public:
    CAdd2DCalibrateFileV2RequestParams(){};
    virtual ~CAdd2DCalibrateFileV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAdd2DCalibrateFileV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAdd2DCalibrateFileV2ResponseBean : public CJsonMessage
{
    virtual ~CAdd2DCalibrateFileV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAdd2DCalibrateFileV2ResponseResult : public CJsonMessage
{
public:
    CAdd2DCalibrateFileV2ResponseResult(){};
    virtual ~CAdd2DCalibrateFileV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADD2DCALIBRATEFILEV2BEAN_H
