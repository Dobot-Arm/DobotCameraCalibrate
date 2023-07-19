#ifndef CURRENTSELECTEDPROJECTBEAN_H
#define CURRENTSELECTEDPROJECTBEAN_H

#include "JsonMessage.h"

struct CCurrentSelectedProjectRequestBean : public CJsonMessage
{
    virtual ~CCurrentSelectedProjectRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CCurrentSelectedProjectRequestParams : public CJsonMessage
{
public:
    CCurrentSelectedProjectRequestParams(){};
    virtual ~CCurrentSelectedProjectRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCurrentSelectedProjectRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCurrentSelectedProjectResponseBean : public CJsonMessage
{
    virtual ~CCurrentSelectedProjectResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString name;
};

class CCurrentSelectedProjectResponseResult : public CJsonMessage
{
public:
    CCurrentSelectedProjectResponseResult(){};
    virtual ~CCurrentSelectedProjectResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCurrentSelectedProjectResponseBean m_data;
};

#endif // CURRENTSELECTEDPROJECTBEAN_H
