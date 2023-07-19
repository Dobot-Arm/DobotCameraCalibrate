#ifndef TAKEBASEPHOTOBEAN_H
#define TAKEBASEPHOTOBEAN_H

#include "JsonMessage.h"
#include "GetProjectRunResultBean.h"

struct CTakeBasePhotoRequestBean : public CJsonMessage
{
    virtual ~CTakeBasePhotoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString savePath;//图片保存的目录，比如E:\test\img\，最后面有斜杠
    bool returnFrame = false; //是否返回图像帧数据
    bool returnResult = false; //true表示返回运行结果数据
    int moduleId = 0; //模块id值
};

class CTakeBasePhotoRequestParams : public CJsonMessage
{
public:
    CTakeBasePhotoRequestParams(){};
    virtual ~CTakeBasePhotoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CTakeBasePhotoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CTakeBasePhotoResponseBean : public CJsonMessage
{
    virtual ~CTakeBasePhotoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString fileName; //图片名称
    QString frame;//图片数据流帧，base64编码
    int width = 0;
    int height = 0;
    CGetProjectRunResultResponseBean2 result;
};

class CTakeBasePhotoResponseResult : public CJsonMessage
{
public:
    CTakeBasePhotoResponseResult(){};
    virtual ~CTakeBasePhotoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CTakeBasePhotoResponseBean m_data;
};

#endif // TAKEBASEPHOTOBEAN_H
