#ifndef GETSUPPORTROIINFOBEAN_H
#define GETSUPPORTROIINFOBEAN_H

#include "JsonMessage.h"

struct CGetSupportRoiInfoRequestBean : public CJsonMessage
{
    virtual ~CGetSupportRoiInfoRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetSupportRoiInfoRequestParams : public CJsonMessage
{
public:
    CGetSupportRoiInfoRequestParams(){};
    virtual ~CGetSupportRoiInfoRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetSupportRoiInfoRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetSupportRoiInfoResponseBean : public CJsonMessage
{
    virtual ~CGetSupportRoiInfoResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString displayNameCN;
    QString displayNameEN;
    QString paramName;
    bool roiFlag = false;
    QString roiEditType;
    QStringList supportRoiType;
    int roiMinCount = 0;
    int roiMaxCount = 0;
    QString matchPointXName;
    QString matchPointYName;
    QString matchPointReset;
};

class CGetSupportRoiInfoResponseResult : public CJsonMessage
{
public:
    CGetSupportRoiInfoResponseResult(){};
    virtual ~CGetSupportRoiInfoResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetSupportRoiInfoResponseBean> m_data;
};

#endif // GETSUPPORTROIINFOBEAN_H
