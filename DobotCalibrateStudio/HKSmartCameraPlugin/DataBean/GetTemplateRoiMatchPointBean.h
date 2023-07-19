#ifndef GETTEMPLATEROIMATCHPOINTBEAN_H
#define GETTEMPLATEROIMATCHPOINTBEAN_H

#include "JsonMessage.h"

struct CGetTemplateRoiMatchPointRequestBean : public CJsonMessage
{
    virtual ~CGetTemplateRoiMatchPointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString matchPointXName;
    QString matchPointYName;
};

class CGetTemplateRoiMatchPointRequestParams : public CJsonMessage
{
public:
    CGetTemplateRoiMatchPointRequestParams(){};
    virtual ~CGetTemplateRoiMatchPointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetTemplateRoiMatchPointRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetTemplateRoiMatchPointResponseBean : public CJsonMessage
{
    virtual ~CGetTemplateRoiMatchPointResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double pointX = 0.0;
    double pointY = 0.0;
};

class CGetTemplateRoiMatchPointResponseResult : public CJsonMessage
{
public:
    CGetTemplateRoiMatchPointResponseResult(){};
    virtual ~CGetTemplateRoiMatchPointResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetTemplateRoiMatchPointResponseBean m_data;
};

#endif // GETTEMPLATEROIMATCHPOINTBEAN_H
