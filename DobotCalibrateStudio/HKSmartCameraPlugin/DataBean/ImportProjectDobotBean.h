#ifndef IMPORTPROJECTDOBOTBEAN_H
#define IMPORTPROJECTDOBOTBEAN_H

#include "JsonMessage.h"

struct CImportProjectDobotRequestBean : public CJsonMessage
{
    virtual ~CImportProjectDobotRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString file; //解决方案全路径，例如E:\project.scsln
};

class CImportProjectDobotRequestParams : public CJsonMessage
{
public:
    CImportProjectDobotRequestParams(){};
    virtual ~CImportProjectDobotRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CImportProjectDobotRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CImportProjectDobotResponseBean : public CJsonMessage
{
    virtual ~CImportProjectDobotResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString content; //要导入的内容
    bool success=true;
    QString msg;
};

class CImportProjectDobotResponseResult : public CJsonMessage
{
public:
    CImportProjectDobotResponseResult(){};
    virtual ~CImportProjectDobotResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CImportProjectDobotResponseBean m_data;
};
#endif // IMPORTPROJECTDOBOTBEAN_H
