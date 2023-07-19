#ifndef SAVEASPROJECTBEAN_H
#define SAVEASPROJECTBEAN_H

#include "JsonMessage.h"

struct CSaveAsProjectRequestBean : public CJsonMessage
{
    virtual ~CSaveAsProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString newSolutionName; //另存为新方案的名称
};

class CSaveAsProjectRequestParams : public CJsonMessage
{
public:
    CSaveAsProjectRequestParams(){};
    virtual ~CSaveAsProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSaveAsProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSaveAsProjectResponseBean : public CJsonMessage
{
    virtual ~CSaveAsProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSaveAsProjectResponseResult : public CJsonMessage
{
public:
    CSaveAsProjectResponseResult(){};
    virtual ~CSaveAsProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SAVEASPROJECTBEAN_H
