#ifndef WRITEPROJECTFILEBEAN_H
#define WRITEPROJECTFILEBEAN_H

#include "JsonMessage.h"

struct CWriteProjectFileRequestBean : public CJsonMessage
{
    virtual ~CWriteProjectFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString projectName;
    QString fileName;
    QString content;
};

class CWriteProjectFileRequestParams : public CJsonMessage
{
public:
    CWriteProjectFileRequestParams(){};
    virtual ~CWriteProjectFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CWriteProjectFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CWriteProjectFileBean : public CJsonMessage
{
    virtual ~CWriteProjectFileBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};
class CWriteProjectFileResponseResult : public CJsonMessage
{
public:
    CWriteProjectFileResponseResult(){};
    virtual ~CWriteProjectFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // WRITEPROJECTFILEBEAN_H
