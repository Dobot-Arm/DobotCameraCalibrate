#ifndef CSTARTTESTVIDEOBEAN_H
#define CSTARTTESTVIDEOBEAN_H

#include "JsonMessage.h"
#include "GetProjectRunResultBean.h"

struct CStartTestVideoRequestBean : public CJsonMessage
{
    virtual ~CStartTestVideoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool returnFrame = false; //是否返回图像帧数据
    bool returnResult = false; //true表示返回运行结果数据
};

class CStartTestVideoRequestParams : public CJsonMessage
{
public:
    CStartTestVideoRequestParams(){};
    virtual ~CStartTestVideoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartTestVideoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStartTestVideoResponseBean : public CJsonMessage
{
    virtual ~CStartTestVideoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame;
    int width = 0;
    int height = 0;
    CGetProjectRunResultResponseBean2 result;
};

class CStartTestVideoResponseResult : public CJsonMessage
{
public:
    CStartTestVideoResponseResult(){};
    virtual ~CStartTestVideoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStartTestVideoResponseBean m_data;
};

#endif // CSTARTVIDEOBEAN_H
