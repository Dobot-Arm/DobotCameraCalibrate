#ifndef CSTOPVIDEOBEAN_H
#define CSTOPVIDEOBEAN_H

#include "JsonMessage.h"

struct CStopVideoRequestBean : public CJsonMessage
{
    virtual ~CStopVideoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CStopVideoRequestParams : public CJsonMessage
{
public:
    CStopVideoRequestParams(){};
    virtual ~CStopVideoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CStopVideoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CStopVideoResponseBean : public CJsonMessage
{
    virtual ~CStopVideoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CStopVideoResponseResult : public CJsonMessage
{
public:
    CStopVideoResponseResult(){};
    virtual ~CStopVideoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};
#endif // CSTOPVIDEOBEAN_H
