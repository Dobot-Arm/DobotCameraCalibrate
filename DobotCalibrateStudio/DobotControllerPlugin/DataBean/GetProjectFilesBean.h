#ifndef GETPROJECTFILESBEAN_H
#define GETPROJECTFILESBEAN_H

#include "JsonMessage.h"

struct CGetProjectFilesRequestBean : public CJsonMessage
{
    virtual ~CGetProjectFilesRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString projectName;
};

class CGetProjectFilesRequestParams : public CJsonMessage
{
public:
    CGetProjectFilesRequestParams(){};
    virtual ~CGetProjectFilesRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetProjectFilesRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetProjectFilesBean : public CJsonMessage
{
    virtual ~CGetProjectFilesBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString fileName;
};
class CGetProjectFilesResponseResult : public CJsonMessage
{
public:
    CGetProjectFilesResponseResult(){};
    virtual ~CGetProjectFilesResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetProjectFilesBean> m_data;
};

#endif // GETPROJECTFILESBEAN_H
