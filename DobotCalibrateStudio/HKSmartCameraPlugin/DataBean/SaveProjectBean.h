#ifndef SAVEPROJECTBEAN_H
#define SAVEPROJECTBEAN_H

#include "JsonMessage.h"

struct CSaveProjectRequestBean : public CJsonMessage
{
    virtual ~CSaveProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString solutionName; //要保存的方案名称
};

class CSaveProjectRequestParams : public CJsonMessage
{
public:
    CSaveProjectRequestParams(){};
    virtual ~CSaveProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSaveProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSaveProjectResponseBean : public CJsonMessage
{
    virtual ~CSaveProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSaveProjectResponseResult : public CJsonMessage
{
public:
    CSaveProjectResponseResult(){};
    virtual ~CSaveProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SAVEPROJECTBEAN_H
