#ifndef CCREATEUSERCOORDINATEV2_H
#define CCREATEUSERCOORDINATEV2_H

#include "JsonMessage.h"

struct CCreateUserCoordinateV2RequestBean : public CJsonMessage
{
    virtual ~CCreateUserCoordinateV2RequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString calibrateFileContent;//标定文件内容。当为空时，忽略type字段，此时使用最后一次标定生成的文件。
    QString type="json";//返回的内容的格式，只能是xml、yml、json中的一种。默认为json格式
    QString savePath; //图片保存的目录，比如E:\test\img\，最后面有斜杠
    bool returnFrame = true; //是否返回图像帧数据
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

class CCreateUserCoordinateV2RequestParams : public CJsonMessage
{
public:
    CCreateUserCoordinateV2RequestParams(){};
    virtual ~CCreateUserCoordinateV2RequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCreateUserCoordinateV2RequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCreateUserCoordinateV2ResultResponseBean : public CJsonMessage
{
    virtual ~CCreateUserCoordinateV2ResultResponseBean(){}
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

class CCreateUserCoordinateV2ResultResponseResult : public CJsonMessage
{
public:
    CCreateUserCoordinateV2ResultResponseResult(){};
    virtual ~CCreateUserCoordinateV2ResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCreateUserCoordinateV2ResultResponseBean m_data;
};

#endif // CCREATEUSERCOORDINATEV2_H
