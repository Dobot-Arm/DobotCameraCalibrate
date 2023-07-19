#ifndef CSTARTVIDEOBEAN_H
#define CSTARTVIDEOBEAN_H

#include "JsonMessage.h"
#include "GetProjectRunResultBean.h"

struct CStartVideoRequestBean : public CJsonMessage
{
    virtual ~CStartVideoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool returnFrame = false; //是否返回图像帧数据
    bool returnResult = false; //true表示返回运行结果数据
};

class CStartVideoRequestParams : public CJsonMessage
{
public:
    CStartVideoRequestParams(){};
    virtual ~CStartVideoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStartVideoResponseBean : public CJsonMessage
{
    virtual ~CStartVideoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame;
    int width = 0;
    int height = 0;
    CGetProjectRunResultResponseBean2 result;
};

class CStartVideoResponseResult : public CJsonMessage
{
public:
    CStartVideoResponseResult(){};
    virtual ~CStartVideoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartVideoResponseBean m_data;
};

#endif // CSTARTVIDEOBEAN_H
