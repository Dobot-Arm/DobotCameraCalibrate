#ifndef GETROICONTOURPOINTSBEAN_H
#define GETROICONTOURPOINTSBEAN_H

#include "JsonMessage.h"

struct CGetRoiContourPointsRequestBean : public CJsonMessage
{
    virtual ~CGetRoiContourPointsRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetRoiContourPointsRequestParams : public CJsonMessage
{
public:
    CGetRoiContourPointsRequestParams(){};
    virtual ~CGetRoiContourPointsRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiContourPointsRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetRoiContourPointsResponseBean : public CJsonMessage
{
    virtual ~CGetRoiContourPointsResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    struct Point2D
    {
        double x;
        double y;
    };
    QList<Point2D> points;
};

class CGetRoiContourPointsResponseResult : public CJsonMessage
{
public:
    CGetRoiContourPointsResponseResult(){};
    virtual ~CGetRoiContourPointsResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetRoiContourPointsResponseBean m_data;
};
#endif // GETROICONTOURPOINTSBEAN_H
