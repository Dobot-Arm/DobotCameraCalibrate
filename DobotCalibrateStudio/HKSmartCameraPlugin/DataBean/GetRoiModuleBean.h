#ifndef GETROIMODULEBEAN_H
#define GETROIMODULEBEAN_H

#include "JsonMessage.h"
#include "RoiType/BaseRoiData.h"
#include "RoiType/BoxRoiData.h"
#include "RoiType/CircleRoiData.h"
#include "RoiType/PolygonRoiData.h"
#include "RoiType/AnnularRoiData.h"
#include "RoiType/UnknowRoiData.h"
#include <QHash>

struct CGetRoiModuleRequestBean : public CJsonMessage
{
    virtual ~CGetRoiModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetRoiModuleRequestParams : public CJsonMessage
{
public:
    CGetRoiModuleRequestParams(){};
    virtual ~CGetRoiModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiModuleRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetRoiModuleResponseBean : public CJsonMessage
{
    virtual ~CGetRoiModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QHash<QString, QList<std::shared_ptr<BaseRoiData>>> roi;
};

class CGetRoiModuleResponseResult : public CJsonMessage
{
public:
    CGetRoiModuleResponseResult(){};
    virtual ~CGetRoiModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiModuleResponseBean m_data;
};

#endif // GETROIMODULEBEAN_H
