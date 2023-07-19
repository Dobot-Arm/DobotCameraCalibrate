#ifndef GETROITEMPLATEBEAN_H
#define GETROITEMPLATEBEAN_H

#include "JsonMessage.h"
#include "RoiType/BaseRoiData.h"
#include "RoiType/BoxRoiData.h"
#include "RoiType/CircleRoiData.h"
#include "RoiType/PolygonRoiData.h"
#include "RoiType/AnnularRoiData.h"
#include "RoiType/UnknowRoiData.h"
#include <QHash>

struct CGetRoiTemplateRequestBean : public CJsonMessage
{
    virtual ~CGetRoiTemplateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetRoiTemplateRequestParams : public CJsonMessage
{
public:
    CGetRoiTemplateRequestParams(){};
    virtual ~CGetRoiTemplateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiTemplateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetRoiTemplateResponseBean : public CJsonMessage
{
    virtual ~CGetRoiTemplateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QHash<QString, QList<std::shared_ptr<BaseRoiData>>> roi;
};

class CGetRoiTemplateResponseResult : public CJsonMessage
{
public:
    CGetRoiTemplateResponseResult(){};
    virtual ~CGetRoiTemplateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiTemplateResponseBean m_data;
};

#endif // GETROITEMPLATEBEAN_H
