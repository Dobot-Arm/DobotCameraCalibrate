#ifndef UPLOADFILEBEAN_H
#define UPLOADFILEBEAN_H

#include "JsonMessage.h"

struct CUploadFileRequestBean : public CJsonMessage
{
    virtual ~CUploadFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString remoteFilePath; //控制器文件全路径，例如：/dobot/userdata/a.json
    QString localFilePath; //本地保存文件全路径，例如：E:\bb.json
};

class CUploadFileRequestParams : public CJsonMessage
{
public:
    CUploadFileRequestParams(){};
    virtual ~CUploadFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CUploadFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CUploadFileResponseBean : public CJsonMessage
{
    virtual ~CUploadFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CUploadFileResponseResult : public CJsonMessage
{
public:
    CUploadFileResponseResult(){};
    virtual ~CUploadFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // UPLOADFILEBEAN_H
