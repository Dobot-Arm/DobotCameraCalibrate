#ifndef CJSONRPCMESSAGE_H
#define CJSONRPCMESSAGE_H

#include <QtGlobal>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "Logger.h"

extern QString createUuid();
extern bool getParamsValue(const QJsonValue& obj, const QString& strKey, bool defaultValue);
extern int getParamsValue(const QJsonValue& obj, const QString& strKey, int defaultValue);
extern unsigned int getParamsValue(const QJsonValue& obj, const QString& strKey, unsigned int defaultValue);
extern double getParamsValue(const QJsonValue& obj, const QString& strKey, double defaultValue);
extern QString getParamsValue(const QJsonValue& obj, const QString& strKey, QString defaultValue);
extern QJsonObject getParamsValue(const QJsonValue& obj, const QString& strKey, QJsonObject defaultValue);
extern QJsonArray getParamsValue(const QJsonValue& obj, const QString& strKey, QJsonArray defaultValue);
extern void setParamsValue(QJsonValue& obj, const QString& strKey, const QJsonValue& newValue);


//msg request cache
typedef struct tagRequestJsonRpcId
{
    QString strSenderId;
    qint64 rpcId;
    QString strApi;
}RequestJsonRpc;

class CJsonMessage
{
public:
    CJsonMessage(){m_bPrintLog=true;}
    virtual ~CJsonMessage(){}

    virtual bool fromJson(const QJsonObject& obj) = 0;
    virtual QJsonObject toJsonObject() const = 0;
    bool fromJson(const QString& strJson);
    QString toJsonString() const;
    inline void setPrintLog(bool b){m_bPrintLog=b;}
    inline bool isPrintLog() const{return m_bPrintLog;}
protected:
    bool m_bPrintLog;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
class CMessageRequest : public CJsonMessage
{
public:
    CMessageRequest();
    CMessageRequest(const CMessageRequest& src);
    CMessageRequest &operator=(const CMessageRequest& src);
    virtual ~CMessageRequest(){}

    void copy(const CMessageRequest& src);

    inline qint64 getId() const {return m_id;}
    inline void setId(qint64 id) {m_id = id;}

    inline QString getMethod() const {return m_strMethod;}
    void setMethod(const QString& strMethod);

    inline QJsonObject getParams() const {return m_params;}
    inline void setParams(const QJsonObject& params) {m_params = params;}

    inline QString getSenderId() const {return m_strSenderId;}
    inline void setSenderId(QString strSenderId) {m_strSenderId = strSenderId;}

    inline QString getMsgUuid() const {return m_strMsgUuid;}
    inline void setMsgUuid(const QString& strGuid) {m_strMsgUuid = strGuid;}

    inline QString getApi() const {return m_strApi;}
    inline QString getPluginName() const {return m_strPluginName;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject() const Q_DECL_OVERRIDE;

private:
    //jsonrpc field
    qint64 m_id;
    QString m_strMethod;
    QJsonObject m_params;

    //extend field
    QString m_strSenderId;
    QString m_strMsgUuid;

    //split from m_strMethod,such as: xxx.xxx.xxx
    QString m_strApi;
    QString m_strPluginName;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
class CMessageResponse : public CJsonMessage
{
public:
    CMessageResponse();
    CMessageResponse(const CMessageResponse& src);
    CMessageResponse(const CMessageRequest& src);
    CMessageResponse &operator=(const CMessageResponse& src);
    virtual ~CMessageResponse(){}

    void copy(const CMessageResponse& src);

    inline qint64 getId() const {return m_id;}
    inline void setId(qint64 id) {m_id = id;}

    inline qint64 getCode() const {return m_code;}
    inline void setCode(qint64 code) {m_code = code;}

    inline QString getErrMsg() const {return m_strErrMsg;}
    inline void setErrMsg(const QString& strErrMsg){m_strErrMsg = strErrMsg;};

    inline QJsonObject getResult() const {return m_result;}
    inline void setResult(const QJsonObject& result) {m_result = result;}

    inline QString getSenderId() const {return m_strSenderId;}
    inline void setSenderId(QString strSenderId) {m_strSenderId = strSenderId;}

    inline QString getMsgUuid() const {return m_strMsgUuid;}
    inline void setMsgUuid(const QString& strGuid) {m_strMsgUuid = strGuid;}

    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject() const Q_DECL_OVERRIDE;

    //过滤掉本不属于协议里面的字段
    QJsonObject toJsonObjectSimple() const;
    QString toJsonStringSimple() const;

private:
    //jsonrpc field
    qint64 m_id;
    qint64 m_code;
    QString m_strErrMsg;
    QJsonObject m_result;

    //extend field
    QString m_strSenderId;
    QString m_strMsgUuid;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
template <typename Type>
bool isParamsContainsValue(const QJsonValue& obj, const QString& strKey)
{
    if (std::is_same<typename std::decay<Type>::type,bool>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isBool());
    }
    else if (std::is_same<typename std::decay<Type>::type,int>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isDouble());
    }
    else if (std::is_same<typename std::decay<Type>::type,int64_t>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isDouble());
    }
    else if (std::is_same<typename std::decay<Type>::type,double>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isDouble());
    }
    else if (std::is_same<typename std::decay<Type>::type,float>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isDouble());
    }
    else if (std::is_same<typename std::decay<Type>::type,QString>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isString());
    }
    else if (std::is_same<typename std::decay<Type>::type,std::string>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isString());
    }
    else if (std::is_same<typename std::decay<Type>::type,QJsonObject>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isObject());
    }
    else if (std::is_same<typename std::decay<Type>::type,QJsonArray>::value)
    {
        if (!obj.isObject()) return false;
        QJsonObject o = obj.toObject();
        return (o.contains(strKey) && o[strKey].isArray());
    }
    return false;
}
#endif // CJSONRPCMESSAGE_H
