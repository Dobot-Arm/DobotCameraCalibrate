#ifndef GET25DCALIBRATEFILELISTBEAN_H
#define GET25DCALIBRATEFILELISTBEAN_H

#include "JsonMessage.h"

struct CGet25DCalibrateFileListRequestBean : public CJsonMessage
{
    virtual ~CGet25DCalibrateFileListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGet25DCalibrateFileListRequestParams : public CJsonMessage
{
public:
    CGet25DCalibrateFileListRequestParams(){};
    virtual ~CGet25DCalibrateFileListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet25DCalibrateFileListRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGet25DCalibrateFileListResponseBean : public CJsonMessage
{
    virtual ~CGet25DCalibrateFileListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString currentFile;
    QString fileType;
    int maxCount;
    QStringList fileList;
};

class CGet25DCalibrateFileListResponseResult : public CJsonMessage
{
public:
    CGet25DCalibrateFileListResponseResult(){};
    virtual ~CGet25DCalibrateFileListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGet25DCalibrateFileListResponseBean m_data;
};

#endif // GET25DCALIBRATEFILELISTBEAN_H
