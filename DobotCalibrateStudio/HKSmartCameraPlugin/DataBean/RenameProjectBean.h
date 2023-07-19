#ifndef RENAMEPROJECTBEAN_H
#define RENAMEPROJECTBEAN_H

#include "JsonMessage.h"

struct CRenameProjectRequestBean : public CJsonMessage
{
    virtual ~CRenameProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //原方案名称
    QString newSolutionName; //重名后的方案名称
};

class CRenameProjectRequestParams : public CJsonMessage
{
public:
    CRenameProjectRequestParams(){};
    virtual ~CRenameProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CRenameProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CRenameProjectResponseBean : public CJsonMessage
{
    virtual ~CRenameProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CRenameProjectResponseResult : public CJsonMessage
{
public:
    CRenameProjectResponseResult(){};
    virtual ~CRenameProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // RENAMEPROJECTBEAN_H
