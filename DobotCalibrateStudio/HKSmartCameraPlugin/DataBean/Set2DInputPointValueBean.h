#ifndef SET2DINPUTPOINTVALUEBEAN_H
#define SET2DINPUTPOINTVALUEBEAN_H

#include "JsonMessage.h"

struct CSet2DInputPointValueRequestBean : public CJsonMessage
{
    virtual ~CSet2DInputPointValueRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int moduleId; //模块id值
    QString paramName;
};

struct CSet2DInputPointValueRequestBean1 : public CJsonMessage
{
    virtual ~CSet2DInputPointValueRequestBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString paramName;
    CSet2DInputPointValueRequestBean parameter;
};

class CSet2DInputPointValueRequestParams : public CJsonMessage
{
public:
    CSet2DInputPointValueRequestParams(){};
    virtual ~CSet2DInputPointValueRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSet2DInputPointValueRequestBean1 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSet2DInputPointValueResponseBean : public CJsonMessage
{
    virtual ~CSet2DInputPointValueResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSet2DInputPointValueResponseResult : public CJsonMessage
{
public:
    CSet2DInputPointValueResponseResult(){};
    virtual ~CSet2DInputPointValueResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SET2DINPUTPOINTVALUEBEAN_H
