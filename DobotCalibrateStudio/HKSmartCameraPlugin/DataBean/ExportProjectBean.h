#ifndef EXPORTPROJECTBEAN_H
#define EXPORTPROJECTBEAN_H

#include "JsonMessage.h"

struct CExportProjectRequestBean : public CJsonMessage
{
    virtual ~CExportProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString saveFile; //保存解决方案全路径，例如E:\project.scsln
    QString solutionName; //要导出的方案名称
};

class CExportProjectRequestParams : public CJsonMessage
{
public:
    CExportProjectRequestParams(){};
    virtual ~CExportProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CExportProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CExportProjectResponseBean : public CJsonMessage
{
    virtual ~CExportProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CExportProjectResponseResult : public CJsonMessage
{
public:
    CExportProjectResponseResult(){};
    virtual ~CExportProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // EXPORTPROJECTBEAN_H
