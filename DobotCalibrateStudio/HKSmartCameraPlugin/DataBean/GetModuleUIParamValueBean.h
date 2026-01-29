#ifndef GETMODULEUIPARAMVALUEBEAN_H
#define GETMODULEUIPARAMVALUEBEAN_H

#include "JsonMessage.h"
#include "UIParamType/UIParamBase.h"
#include "UIParamType/UIParamBoolean.h"
#include "UIParamType/UIParamCommand.h"
#include "UIParamType/UIParamEnumeration.h"
#include "UIParamType/UIParamFloat.h"
#include "UIParamType/UIParamInteger.h"
#include "UIParamType/UIParamString.h"
#include "UIParamType/UIParamUnknow.h"
#include <memory>

struct CGetModuleUIParamValueRequestBean0 : public CJsonMessage
{
    virtual ~CGetModuleUIParamValueRequestBean0(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramType;
};

struct CGetModuleUIParamValueRequestBean : public CJsonMessage
{
    virtual ~CGetModuleUIParamValueRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QList<CGetModuleUIParamValueRequestBean0> parameters; //参数名称数组
};

class CGetModuleUIParamValueRequestParams : public CJsonMessage
{
public:
    CGetModuleUIParamValueRequestParams(){};
    virtual ~CGetModuleUIParamValueRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleUIParamValueRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetModuleUIParamValueResponseBean : public CJsonMessage
{
    virtual ~CGetModuleUIParamValueResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramType; //UIParamBase::getType()
    std::shared_ptr<UIParamBase> parameters;
};

class CGetModuleUIParamValueResponseResult : public CJsonMessage
{
public:
    CGetModuleUIParamValueResponseResult(){};
    virtual ~CGetModuleUIParamValueResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetModuleUIParamValueResponseBean> m_data;
};

#endif // GETMODULEUIPARAMVALUEBEAN_H
