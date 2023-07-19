#ifndef GET2DINPUTPOINTVALUEBEAN_H
#define GET2DINPUTPOINTVALUEBEAN_H

#include "JsonMessage.h"

struct CGet2DInputPointValueRequestBean : public CJsonMessage
{
    virtual ~CGet2DInputPointValueRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGet2DInputPointValueRequestParams : public CJsonMessage
{
public:
    CGet2DInputPointValueRequestParams(){};
    virtual ~CGet2DInputPointValueRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DInputPointValueRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGet2DInputPointValueResponseBean1 : public CJsonMessage
{
    virtual ~CGet2DInputPointValueResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString displayNameCN;
    QString displayNameEN;
    QString paramName;
    QString paramNameCN;
    QString paramNameEN;
};
struct CGet2DInputPointValueResponseBean2 : public CJsonMessage
{
    virtual ~CGet2DInputPointValueResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    CGet2DInputPointValueResponseBean1 runPointX;
    CGet2DInputPointValueResponseBean1 runPointY;
    CGet2DInputPointValueResponseBean1 runPointAngle;
};

class CGet2DInputPointValueResponseResult : public CJsonMessage
{
public:
    CGet2DInputPointValueResponseResult(){};
    virtual ~CGet2DInputPointValueResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DInputPointValueResponseBean2 m_data;
};
#endif // GET2DINPUTPOINTVALUEBEAN_H
