#ifndef ADD25DCALIBRATEFILEV2BEAN_H
#define ADD25DCALIBRATEFILEV2BEAN_H

#include "JsonMessage.h"

struct CAdd25DCalibrateFileV2RequestBean : public CJsonMessage
{
    virtual ~CAdd25DCalibrateFileV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString fileContent;
};

class CAdd25DCalibrateFileV2RequestParams : public CJsonMessage
{
public:
    CAdd25DCalibrateFileV2RequestParams(){};
    virtual ~CAdd25DCalibrateFileV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAdd25DCalibrateFileV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAdd25DCalibrateFileV2ResponseBean : public CJsonMessage
{
    virtual ~CAdd25DCalibrateFileV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAdd25DCalibrateFileV2ResponseResult : public CJsonMessage
{
public:
    CAdd25DCalibrateFileV2ResponseResult(){};
    virtual ~CAdd25DCalibrateFileV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADD25DCALIBRATEFILEBEAN_H
