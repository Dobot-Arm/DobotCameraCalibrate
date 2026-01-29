#ifndef EXPORTPROJECTDOBOTBEAN_H
#define EXPORTPROJECTDOBOTBEAN_H

#include "JsonMessage.h"

struct CExportProjectDobotRequestBean : public CJsonMessage
{
    virtual ~CExportProjectDobotRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString saveFile; //保存解决方案全路径，例如E:\project.scsln
    QString solutionName; //要导出的方案名称
    QString content; //要导出的内容
};

class CExportProjectDobotRequestParams : public CJsonMessage
{
public:
    CExportProjectDobotRequestParams(){};
    virtual ~CExportProjectDobotRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CExportProjectDobotRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CExportProjectDobotResponseBean : public CJsonMessage
{
    virtual ~CExportProjectDobotResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CExportProjectDobotResponseResult : public CJsonMessage
{
public:
    CExportProjectDobotResponseResult(){};
    virtual ~CExportProjectDobotResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // EXPORTPROJECTDOBOTBEAN_H
