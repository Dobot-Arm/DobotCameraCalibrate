#ifndef ADDMODULEBEAN_H
#define ADDMODULEBEAN_H

#include "JsonMessage.h"

struct CAddModuleRequestBean : public CJsonMessage
{
    virtual ~CAddModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int preModuleId = 0; //前序模块id，这个值通常是0，在分支逻辑模块下面添加子模块时用到
};

class CAddModuleRequestParams : public CJsonMessage
{
public:
    CAddModuleRequestParams(){};
    virtual ~CAddModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAddModuleRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAddModuleResponseBean : public CJsonMessage
{
    virtual ~CAddModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAddModuleResponseResult : public CJsonMessage
{
public:
    CAddModuleResponseResult(){};
    virtual ~CAddModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADDMODULEBEAN_H
