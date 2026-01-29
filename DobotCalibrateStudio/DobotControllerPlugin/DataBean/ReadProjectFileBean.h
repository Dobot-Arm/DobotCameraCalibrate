#ifndef READPROJECTFILEBEAN_H
#define READPROJECTFILEBEAN_H

#include "JsonMessage.h"

struct CReadProjectFileRequestBean : public CJsonMessage
{
    virtual ~CReadProjectFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString projectName;
    QString fileName;
};

class CReadProjectFileRequestParams : public CJsonMessage
{
public:
    CReadProjectFileRequestParams(){};
    virtual ~CReadProjectFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CReadProjectFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CReadProjectFileBean : public CJsonMessage
{
    virtual ~CReadProjectFileBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString content;
};
class CReadProjectFileResponseResult : public CJsonMessage
{
public:
    CReadProjectFileResponseResult(){};
    virtual ~CReadProjectFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CReadProjectFileBean m_data;
};

#endif // READPROJECTFILEBEAN_H
