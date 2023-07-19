#ifndef GET2DCALIBRATEFILELISTBEAN_H
#define GET2DCALIBRATEFILELISTBEAN_H

#include "JsonMessage.h"

struct CGet2DCalibrateFileListRequestBean : public CJsonMessage
{
    virtual ~CGet2DCalibrateFileListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGet2DCalibrateFileListRequestParams : public CJsonMessage
{
public:
    CGet2DCalibrateFileListRequestParams(){};
    virtual ~CGet2DCalibrateFileListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DCalibrateFileListRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGet2DCalibrateFileListResponseBean : public CJsonMessage
{
    virtual ~CGet2DCalibrateFileListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString currentFile;
    QString fileType;
    int maxCount;
    QStringList fileList;
};

class CGet2DCalibrateFileListResponseResult : public CJsonMessage
{
public:
    CGet2DCalibrateFileListResponseResult(){};
    virtual ~CGet2DCalibrateFileListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet2DCalibrateFileListResponseBean m_data;
};

#endif // GET2DCALIBRATEFILELISTBEAN_H
