#ifndef RESETTEMPLATEROIMATCHPOINTBEAN_H
#define RESETTEMPLATEROIMATCHPOINTBEAN_H

#include "JsonMessage.h"

struct CResetTemplateRoiMatchPointRequestBean : public CJsonMessage
{
    virtual ~CResetTemplateRoiMatchPointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString matchPointReset;
};

class CResetTemplateRoiMatchPointRequestParams : public CJsonMessage
{
public:
    CResetTemplateRoiMatchPointRequestParams(){};
    virtual ~CResetTemplateRoiMatchPointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CResetTemplateRoiMatchPointRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CResetTemplateRoiMatchPointResponseBean : public CJsonMessage
{
    virtual ~CResetTemplateRoiMatchPointResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CResetTemplateRoiMatchPointResponseResult : public CJsonMessage
{
public:
    CResetTemplateRoiMatchPointResponseResult(){};
    virtual ~CResetTemplateRoiMatchPointResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CResetTemplateRoiMatchPointResponseBean m_data;
};

#endif // RESETTEMPLATEROIMATCHPOINTBEAN_H
