#ifndef GETINFOLISTBEAN_H
#define GETINFOLISTBEAN_H

#include "JsonMessage.h"

struct CGetInfoListRequestBean : public CJsonMessage
{
    virtual ~CGetInfoListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString ip; //控制器ip地址
    int port = 22;
    QString directory; //路径
    QString type; //类型，"file"表示只返回文件，"dir"表示只返回目录，其它值表示返回所有文件和目录，可以不填，表示返回所有
};

class CGetInfoListRequestParams : public CJsonMessage
{
public:
    CGetInfoListRequestParams(){};
    virtual ~CGetInfoListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetInfoListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetInfoListBean : public CJsonMessage
{
    virtual ~CGetInfoListBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString name;
    QString type;
    qint64 size;
};
class CGetInfoListResponseResult : public CJsonMessage
{
public:
    CGetInfoListResponseResult(){};
    virtual ~CGetInfoListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetInfoListBean> m_data;
};

#endif // GETINFOLISTBEAN_H
