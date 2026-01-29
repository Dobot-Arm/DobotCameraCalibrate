#ifndef GETMODULECALIBRATEFILELISTBEAN_H
#define GETMODULECALIBRATEFILELISTBEAN_H

#include "JsonMessage.h"

struct CGetModuleCalibrateFileListRequestBean : public CJsonMessage
{
    virtual ~CGetModuleCalibrateFileListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetModuleCalibrateFileListRequestParams : public CJsonMessage
{
public:
    CGetModuleCalibrateFileListRequestParams(){};
    virtual ~CGetModuleCalibrateFileListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleCalibrateFileListRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetModuleCalibrateFileListResponseBean : public CJsonMessage
{
    virtual ~CGetModuleCalibrateFileListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString currentFile;
    QString fileType;
    int maxCount;
    QStringList fileList;
};

class CGetModuleCalibrateFileListResponseResult : public CJsonMessage
{
public:
    CGetModuleCalibrateFileListResponseResult(){};
    virtual ~CGetModuleCalibrateFileListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleCalibrateFileListResponseBean m_data;
};

#endif // GETMODULECALIBRATEFILELISTBEAN_H
