#ifndef CAMERASOFTREBOOTBEAN_H
#define CAMERASOFTREBOOTBEAN_H

#include "JsonMessage.h"

struct CCameraSoftRebootRequestBean : public CJsonMessage
{
    virtual ~CCameraSoftRebootRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCameraSoftRebootRequestParams : public CJsonMessage
{
public:
    CCameraSoftRebootRequestParams(){};
    virtual ~CCameraSoftRebootRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCameraSoftRebootRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCameraSoftRebootResponseBean : public CJsonMessage
{
    virtual ~CCameraSoftRebootResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CCameraSoftRebootResponseResult : public CJsonMessage
{
public:
    CCameraSoftRebootResponseResult(){};
    virtual ~CCameraSoftRebootResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};
#endif // CAMERASOFTREBOOTBEAN_H
