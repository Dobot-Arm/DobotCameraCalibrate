#ifndef SETROITEMPLATEBEAN_H
#define SETROITEMPLATEBEAN_H

#include "JsonMessage.h"
#include "RoiType/BaseRoiData.h"
#include "RoiType/BoxRoiData.h"
#include "RoiType/CircleRoiData.h"
#include "RoiType/PolygonRoiData.h"
#include "RoiType/AnnularRoiData.h"
#include "RoiType/UnknowRoiData.h"
#include <QHash>

struct CSetRoiTemplateRequestBean : public CJsonMessage
{
    virtual ~CSetRoiTemplateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QHash<QString, QList<std::shared_ptr<BaseRoiData>>> roi;
};

class CSetRoiTemplateRequestParams : public CJsonMessage
{
public:
    CSetRoiTemplateRequestParams(){};
    virtual ~CSetRoiTemplateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetRoiTemplateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetRoiTemplateResponseBean : public CJsonMessage
{
    virtual ~CSetRoiTemplateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetRoiTemplateResponseResult : public CJsonMessage
{
public:
    CSetRoiTemplateResponseResult(){};
    virtual ~CSetRoiTemplateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetRoiTemplateResponseBean m_data;
};

#endif // SETROITEMPLATEBEAN_H
