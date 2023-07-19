#ifndef CCREATEUSERCOORDINATE_H
#define CCREATEUSERCOORDINATE_H

#include "JsonMessage.h"

struct CCreateUserCoordinateRequestBean : public CJsonMessage
{
    virtual ~CCreateUserCoordinateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString calibrateFile;//标定文件完整路径，文件后缀名只能是xml、yml、json中的一种类型，比如E:\test\CalibratedTransform.json
    QString savePath; //图片保存的目录，比如E:\test\img\，最后面有斜杠
    bool returnFrame = false; //是否返回图像帧数据
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

class CCreateUserCoordinateRequestParams : public CJsonMessage
{
public:
    CCreateUserCoordinateRequestParams(){};
    virtual ~CCreateUserCoordinateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCreateUserCoordinateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCreateUserCoordinateResultResponseBean : public CJsonMessage
{
    virtual ~CCreateUserCoordinateResultResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
    int id = -1; //标定板序列号
    QString frame; //图片数据流帧，base64编码
    QString fileName; //生成的图片名称，比如 a.bmp
};

class CCreateUserCoordinateResultResponseResult : public CJsonMessage
{
public:
    CCreateUserCoordinateResultResponseResult(){};
    virtual ~CCreateUserCoordinateResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCreateUserCoordinateResultResponseBean m_data;
};

#endif // CCREATEUSERCOORDINATE_H
