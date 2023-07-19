#ifndef BASEIMAGEHISTORYIMAGEINFOLISTBEAN_H
#define BASEIMAGEHISTORYIMAGEINFOLISTBEAN_H

#include "JsonMessage.h"

struct CBaseImageHistoryImageInfoListRequestBean : public CJsonMessage
{
    virtual ~CBaseImageHistoryImageInfoListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CBaseImageHistoryImageInfoListRequestParams : public CJsonMessage
{
public:
    CBaseImageHistoryImageInfoListRequestParams(){};
    virtual ~CBaseImageHistoryImageInfoListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CBaseImageHistoryImageInfoListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CBaseImageHistoryImageInfoListResponseBean : public CJsonMessage
{
    virtual ~CBaseImageHistoryImageInfoListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString imageName;
    QString imageDate;
    bool imageState = false;
};

class CBaseImageHistoryImageInfoListResponseResult : public CJsonMessage
{
public:
    CBaseImageHistoryImageInfoListResponseResult(){};
    virtual ~CBaseImageHistoryImageInfoListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CBaseImageHistoryImageInfoListResponseBean> m_data;
};


#endif // BASEIMAGEHISTORYIMAGEINFOLISTBEAN_H
