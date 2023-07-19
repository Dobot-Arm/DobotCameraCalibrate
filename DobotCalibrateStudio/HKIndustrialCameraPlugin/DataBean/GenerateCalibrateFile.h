#ifndef CGENERATECALIBRATEFILE_H
#define CGENERATECALIBRATEFILE_H

#include "JsonMessage.h"

struct CGenerateCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CGenerateCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString saveFileFullName;//标定文件保存完整路径，文件后缀名只能是xml、yml、json中的一种类型，比如E:\test\CalibratedTransform.json
};

class CGenerateCalibrateFileRequestParams : public CJsonMessage
{
public:
    CGenerateCalibrateFileRequestParams(){};
    virtual ~CGenerateCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGenerateCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGenerateCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CGenerateCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CGenerateCalibrateFileResponseResult : public CJsonMessage
{
public:
    CGenerateCalibrateFileResponseResult(){};
    virtual ~CGenerateCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // CGENERATECALIBRATEFILE_H
