#ifndef CTAKEPHOTOBEAN_H
#define CTAKEPHOTOBEAN_H

#include "JsonMessage.h"

struct CTakePhotoRequestBean : public CJsonMessage
{
    virtual ~CTakePhotoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString savePath;//图片保存的目录，比如E:\test\img\，最后面有斜杠
};

class CTakePhotoRequestParams : public CJsonMessage
{
public:
    CTakePhotoRequestParams(){};
    virtual ~CTakePhotoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CTakePhotoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CTakePhotoResponseBean : public CJsonMessage
{
    virtual ~CTakePhotoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString fileName; //图片名称
    QString frame;//图片数据流帧，base64编码
};

class CTakePhotoResponseResult : public CJsonMessage
{
public:
    CTakePhotoResponseResult(){};
    virtual ~CTakePhotoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CTakePhotoResponseBean m_data;
};

#endif // CTAKEPHOTOBEAN_H
