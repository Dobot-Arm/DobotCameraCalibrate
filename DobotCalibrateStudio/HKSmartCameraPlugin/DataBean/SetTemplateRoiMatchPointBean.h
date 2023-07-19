#ifndef SETTEMPLATEROIMATCHPOINTBEAN_H
#define SETTEMPLATEROIMATCHPOINTBEAN_H

#include "JsonMessage.h"

struct CSetTemplateRoiMatchPointRequestBean : public CJsonMessage
{
    virtual ~CSetTemplateRoiMatchPointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString matchPointXName;
    double pointX = 0.0;
    QString matchPointYName;
    double pointY = 0.0;
};

class CSetTemplateRoiMatchPointRequestParams : public CJsonMessage
{
public:
    CSetTemplateRoiMatchPointRequestParams(){};
    virtual ~CSetTemplateRoiMatchPointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetTemplateRoiMatchPointRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetTemplateRoiMatchPointResponseBean : public CJsonMessage
{
    virtual ~CSetTemplateRoiMatchPointResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetTemplateRoiMatchPointResponseResult : public CJsonMessage
{
public:
    CSetTemplateRoiMatchPointResponseResult(){};
    virtual ~CSetTemplateRoiMatchPointResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetTemplateRoiMatchPointResponseBean m_data;
};

#endif // SETTEMPLATEROIMATCHPOINTBEAN_H
