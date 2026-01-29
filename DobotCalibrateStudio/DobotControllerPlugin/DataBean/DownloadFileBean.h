#ifndef DOWNLOADFILEBEAN_H
#define DOWNLOADFILEBEAN_H

#include "JsonMessage.h"

struct CDownloadFileRequestBean : public CJsonMessage
{
    virtual ~CDownloadFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString remoteFilePath; //控制器文件全路径，例如：/dobot/userdata/a.json
    QString localFilePath; //本地保存文件全路径，例如：E:\bb.json
};

class CDownloadFileRequestParams : public CJsonMessage
{
public:
    CDownloadFileRequestParams(){};
    virtual ~CDownloadFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDownloadFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDownloadFileResponseBean : public CJsonMessage
{
    virtual ~CDownloadFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDownloadFileResponseResult : public CJsonMessage
{
public:
    CDownloadFileResponseResult(){};
    virtual ~CDownloadFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DOWNLOADFILEBEAN_H
