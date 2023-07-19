#ifndef CGENERATECALIBRATEFILEV2_H
#define CGENERATECALIBRATEFILEV2_H

#include "JsonMessage.h"

struct CGenerateCalibrateFileV2RequestBean : public CJsonMessage
{
    virtual ~CGenerateCalibrateFileV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString type="json";//返回的内容的格式，只能是xml、yml、json中的一种。默认为json格式
};

class CGenerateCalibrateFileV2RequestParams : public CJsonMessage
{
public:
    CGenerateCalibrateFileV2RequestParams(){};
    virtual ~CGenerateCalibrateFileV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGenerateCalibrateFileV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGenerateCalibrateFileV2ResponseBean : public CJsonMessage
{
    virtual ~CGenerateCalibrateFileV2ResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString content; //标定文件内容
};

class CGenerateCalibrateFileV2ResponseResult : public CJsonMessage
{
public:
    CGenerateCalibrateFileV2ResponseResult(){};
    virtual ~CGenerateCalibrateFileV2ResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGenerateCalibrateFileV2ResponseBean m_data;
};

#endif // CGENERATECALIBRATEFILEV2_H
