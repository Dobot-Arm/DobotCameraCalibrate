#ifndef GETMODULEUIALLPARAMETERBEAN_H
#define GETMODULEUIALLPARAMETERBEAN_H

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

struct CGetModuleUIAllParameterRequestBean : public CJsonMessage
{
    virtual ~CGetModuleUIAllParameterRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QStringList parameters; //参数名称数组
};

class CGetModuleUIAllParameterRequestParams : public CJsonMessage
{
public:
    CGetModuleUIAllParameterRequestParams(){};
    virtual ~CGetModuleUIAllParameterRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleUIAllParameterRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetModuleUIAllParameterResponseBean : public CJsonMessage
{
    virtual ~CGetModuleUIAllParameterResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    bool visible = true;
    QString displayNameCN;
    QString displayNameEN;
    QString paramType; //UIParamBase::getType()
    std::shared_ptr<UIParamBase> parameters;
};

class CGetModuleUIAllParameterResponseResult : public CJsonMessage
{
public:
    CGetModuleUIAllParameterResponseResult(){};
    virtual ~CGetModuleUIAllParameterResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetModuleUIAllParameterResponseBean> m_data;
};

#endif // GETMODULEUIALLPARAMETERBEAN_H
