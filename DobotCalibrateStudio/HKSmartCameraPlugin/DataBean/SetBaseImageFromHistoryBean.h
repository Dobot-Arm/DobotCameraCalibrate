#ifndef SETBASEIMAGEFROMHISTORYBEAN_H
#define SETBASEIMAGEFROMHISTORYBEAN_H

#include "JsonMessage.h"

struct CSetBaseImageFromHistoryRequestBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromHistoryRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString imageName; //历史图像名称
};

class CSetBaseImageFromHistoryRequestParams : public CJsonMessage
{
public:
    CSetBaseImageFromHistoryRequestParams(){};
    virtual ~CSetBaseImageFromHistoryRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetBaseImageFromHistoryRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetBaseImageFromHistoryResponseBean : public CJsonMessage
{
    virtual ~CSetBaseImageFromHistoryResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetBaseImageFromHistoryResponseResult : public CJsonMessage
{
public:
    CSetBaseImageFromHistoryResponseResult(){};
    virtual ~CSetBaseImageFromHistoryResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETBASEIMAGEFROMHISTORYBEAN_H
