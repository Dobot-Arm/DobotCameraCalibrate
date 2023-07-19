#ifndef CTAKEPHOTOBEAN_H
#define CTAKEPHOTOBEAN_H

#include "JsonMessage.h"
#include "GetProjectRunResultBean.h"

struct CTakePhotoRequestBean : public CJsonMessage
{
    virtual ~CTakePhotoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString savePath;//图片保存的目录，比如E:\test\img\，最后面有斜杠
    bool returnFrame = false; //是否返回图像帧数据
    bool returnResult = false; //true表示返回运行结果数据
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
    int width = 0;
    int height = 0;
    CGetProjectRunResultResponseBean2 result;
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
