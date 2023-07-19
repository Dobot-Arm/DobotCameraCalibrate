#ifndef IMPORTPROJECTBEAN_H
#define IMPORTPROJECTBEAN_H

#include "JsonMessage.h"

struct CImportProjectRequestBean : public CJsonMessage
{
    virtual ~CImportProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString file; //解决方案全路径，例如E:\project.scsln
};

class CImportProjectRequestParams : public CJsonMessage
{
public:
    CImportProjectRequestParams(){};
    virtual ~CImportProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CImportProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CImportProjectResponseBean : public CJsonMessage
{
    virtual ~CImportProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CImportProjectResponseResult : public CJsonMessage
{
public:
    CImportProjectResponseResult(){};
    virtual ~CImportProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};
#endif // IMPORTPROJECTBEAN_H
