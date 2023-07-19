#ifndef SETROIMODULEBEAN_H
#define SETROIMODULEBEAN_H

#include "JsonMessage.h"
#include "RoiType/BaseRoiData.h"
#include "RoiType/BoxRoiData.h"
#include "RoiType/CircleRoiData.h"
#include "RoiType/PolygonRoiData.h"
#include "RoiType/AnnularRoiData.h"
#include "RoiType/UnknowRoiData.h"
#include <QHash>

struct CSetRoiModuleRequestBean : public CJsonMessage
{
    virtual ~CSetRoiModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QHash<QString, QList<std::shared_ptr<BaseRoiData>>> roi;
};

class CSetRoiModuleRequestParams : public CJsonMessage
{
public:
    CSetRoiModuleRequestParams(){};
    virtual ~CSetRoiModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetRoiModuleRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetRoiModuleResponseBean : public CJsonMessage
{
    virtual ~CSetRoiModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetRoiModuleResponseResult : public CJsonMessage
{
public:
    CSetRoiModuleResponseResult(){};
    virtual ~CSetRoiModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetRoiModuleResponseBean m_data;
};

#endif // SETROIMODULEBEAN_H
