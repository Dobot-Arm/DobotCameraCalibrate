#ifndef REUSETRANSFORM_H
#define REUSETRANSFORM_H

#include "JsonMessage.h"

struct CReuseTransformBean : public CJsonMessage
{
    virtual ~CReuseTransformBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CToolTransformationRequestBean : public CJsonMessage
{
    virtual ~CToolTransformationRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    CReuseTransformBean oldPoint;
    CReuseTransformBean newPoint;
};

class CToolTransformationRequestParams : public CJsonMessage
{
public:
    CToolTransformationRequestParams(){};
    virtual ~CToolTransformationRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CToolTransformationRequestBean m_data;
};
/*********************************************************************************************************/
class CToolTransformationResultResponseResult : public CJsonMessage
{
public:
    CToolTransformationResultResponseResult(){};
    virtual ~CToolTransformationResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<double> m_data; //工具变换RT值，长度为16的数组
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAxisTransformationRequestBean : public CJsonMessage
{
    virtual ~CAxisTransformationRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QList<CReuseTransformBean> oldPoints;
    QList<CReuseTransformBean> newPoints;
};

class CAxisTransformationRequestParams : public CJsonMessage
{
public:
    CAxisTransformationRequestParams(){};
    virtual ~CAxisTransformationRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAxisTransformationRequestBean m_data;
};
/*********************************************************************************************************/
class CAxisTransformationResultResponseResult : public CJsonMessage
{
public:
    CAxisTransformationResultResponseResult(){};
    virtual ~CAxisTransformationResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<double> m_data; //坐标系变换RT值，长度为16的数组
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CReusePointRequestBean : public CJsonMessage
{
    virtual ~CReusePointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    CReuseTransformBean srcPoint;
    QList<double> toolRT; //工具变换RT1值，长度为16的数组
    QList<double> coordRT; //坐标系变换RT2，长度为16的数组
};

class CReusePointRequestParams : public CJsonMessage
{
public:
    CReusePointRequestParams(){};
    virtual ~CReusePointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CReusePointRequestBean m_data;
};
/*********************************************************************************************************/
class CReusePointResultResponseResult : public CJsonMessage
{
public:
    CReusePointResultResponseResult(){};
    virtual ~CReusePointResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CReuseTransformBean m_data;
};
#endif // REUSETRANSFORM_H
