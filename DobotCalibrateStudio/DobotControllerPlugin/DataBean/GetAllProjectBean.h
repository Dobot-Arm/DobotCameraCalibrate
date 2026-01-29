#ifndef GETALLPROJECTBEAN_H
#define GETALLPROJECTBEAN_H

#include "JsonMessage.h"

struct CGetAllProjectRequestBean : public CJsonMessage
{
    virtual ~CGetAllProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
};

class CGetAllProjectRequestParams : public CJsonMessage
{
public:
    CGetAllProjectRequestParams(){};
    virtual ~CGetAllProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetAllProjectRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetAllProjectBean : public CJsonMessage
{
    virtual ~CGetAllProjectBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString projectName;
};
class CGetAllProjectResponseResult : public CJsonMessage
{
public:
    CGetAllProjectResponseResult(){};
    virtual ~CGetAllProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetAllProjectBean> m_data;
};

#endif // GETALLPROJECTBEAN_H
