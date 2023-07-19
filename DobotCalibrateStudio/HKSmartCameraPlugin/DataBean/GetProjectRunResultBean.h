#ifndef GETPROJECTRUNRESULTBEAN_H
#define GETPROJECTRUNRESULTBEAN_H

#include "JsonMessage.h"
#include "RunResult/BaseRunResult.h"
#include "RunResult/MacapriltagRunResult.h"
#include "RunResult/ImageExistRunResult.h"
#include "RunResult/DiameterMeasureRunResult.h"
#include "RunResult/WidthMeasureRunResult.h"
#include "RunResult/IdeModuleRunResult.h"
#include "RunResult/DlocrDetectRunResult.h"
#include "RunResult/GreyAreaRunResult.h"
#include "RunResult/MatchCalibRunResult.h"
#include "RunResult/MatchLocateRunResult.h"

struct CGetProjectRunResultRequestBean : public CJsonMessage
{
    virtual ~CGetProjectRunResultRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QStringList allModuleName;
};

class CGetProjectRunResultRequestParams : public CJsonMessage
{
public:
    CGetProjectRunResultRequestParams(){};
    virtual ~CGetProjectRunResultRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetProjectRunResultRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetProjectRunResultResponseBean : public CJsonMessage
{
    virtual ~CGetProjectRunResultResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId = 0;
    QString result="NG";
    QString resultRefCN;
    QString resultRefEN;
    std::shared_ptr<BaseRunResult> moduleData;
};

struct CGetProjectRunResultResponseBean2 : public CJsonMessage
{
    virtual ~CGetProjectRunResultResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    void clear();

    QString solutionName;
    int totalNumber = 0;
    int ngNumber = 0;
    QString result="NG";
    QList<CGetProjectRunResultResponseBean> data;
};

class CGetProjectRunResultResponseResult : public CJsonMessage
{
public:
    CGetProjectRunResultResponseResult(){};
    virtual ~CGetProjectRunResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetProjectRunResultResponseBean2 m_data;
};

#endif // GETPROJECTRUNRESULTBEAN_H
