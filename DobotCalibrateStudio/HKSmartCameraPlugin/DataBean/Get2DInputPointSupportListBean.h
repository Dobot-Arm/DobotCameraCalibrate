#ifndef GET2DINPUTPOINTSUPPORTLISTBEAN_H
#define GET2DINPUTPOINTSUPPORTLISTBEAN_H

#include "JsonMessage.h"

struct CGet2DInputPointSupportListRequestBean : public CJsonMessage
{
    virtual ~CGet2DInputPointSupportListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGet2DInputPointSupportListRequestParams : public CJsonMessage
{
public:
    CGet2DInputPointSupportListRequestParams(){};
    virtual ~CGet2DInputPointSupportListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DInputPointSupportListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGet2DInputPointSupportListResponseBean1 : public CJsonMessage
{
    virtual ~CGet2DInputPointSupportListResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramNameCN;
    QString paramNameEN;
};

struct CGet2DInputPointSupportListResponseBean2 : public CJsonMessage
{
    virtual ~CGet2DInputPointSupportListResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString displayNameCN;
    QString displayNameEN;
    QList<CGet2DInputPointSupportListResponseBean1> subParamList;
};

struct CGet2DInputPointSupportListResponseBean3 : public CJsonMessage
{
    virtual ~CGet2DInputPointSupportListResponseBean3(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QList<CGet2DInputPointSupportListResponseBean2> runPointX;
    QList<CGet2DInputPointSupportListResponseBean2> runPointY;
    QList<CGet2DInputPointSupportListResponseBean2> runPointAngle;
};

class CGet2DInputPointSupportListResponseResult : public CJsonMessage
{
public:
    CGet2DInputPointSupportListResponseResult(){};
    virtual ~CGet2DInputPointSupportListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DInputPointSupportListResponseBean3 m_data;
};
#endif // GET2DINPUTPOINTSUPPORTLISTBEAN_H
