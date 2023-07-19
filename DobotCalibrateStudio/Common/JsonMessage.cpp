#include "JsonMessage.h"

#include <QUuid>

QString createUuid()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

bool CJsonMessage::fromJson(const QString &strJson)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8(), &error);
    if (QJsonParseError::NoError != error.error)
    {
        qCritical()<<"json parse error:"<<error.errorString();
        return false;
    }
    if (!doc.isObject())
    {
        qCritical()<<"json is not a object!";
        return false;
    }
    return fromJson(doc.object());
}

QString CJsonMessage::toJsonString() const
{
    QJsonDocument doc(toJsonObject());
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
CMessageRequest::CMessageRequest()
{
    m_id = 0;
    m_strMsgUuid = createUuid();
}

CMessageRequest::CMessageRequest(const CMessageRequest &src)
{
    if (this != &src) copy(src);
}

CMessageRequest &CMessageRequest::operator=(const CMessageRequest &src)
{
    if (this != &src) copy(src);
    return *this;
}

void CMessageRequest::copy(const CMessageRequest &src)
{
    m_id = src.m_id;
    m_strMethod = src.m_strMethod;
    m_params = src.m_params;

    m_strSenderId = src.m_strSenderId;
    m_strMsgUuid = src.m_strMsgUuid;
    m_strPluginName = src.m_strPluginName;
    m_strApi = src.m_strApi;
}

void CMessageRequest::setMethod(const QString &strMethod)
{
    m_strMethod = strMethod;
    QStringList all = m_strMethod.split('.');
    if (all.size() >= 2)
    {
        m_strPluginName = all[0]+'.'+all[1];
    }
    if (all.size() >= 3)
    {
        m_strApi = all[2];
    }
}

bool CMessageRequest::fromJson(const QJsonObject &obj)
{
    if (obj.contains("id") && obj["id"].isDouble())
    {
        setId(obj["id"].toVariant().toLongLong());
    }
    if (obj.contains("method") && obj["method"].isString())
    {
        setMethod(obj["method"].toString());
    }
    if (obj.contains("params") && obj["params"].isObject())
    {
        setParams(obj["params"].toObject());
    }

    if (obj.contains("senderId") && obj["senderId"].isString())
    {
        setSenderId(obj["senderId"].toString());
    }
    if (obj.contains("msgUuid") && obj["msgUuid"].isString())
    {
        setMsgUuid(obj["msgUuid"].toString());
    }
    if (obj.contains("isPrintLog") && obj["isPrintLog"].isBool())
    {
        setPrintLog(obj["isPrintLog"].toBool());
    }

    return true;
}

QJsonObject CMessageRequest::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("id",getId());
    obj.insert("method",getMethod());
    obj.insert("params",getParams());

    obj.insert("senderId",getSenderId());
    obj.insert("msgUuid",getMsgUuid());
    obj.insert("isPrintLog",isPrintLog());

    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
CMessageResponse::CMessageResponse()
{
    m_id = 0;
    m_code = 0;
    m_strMsgUuid = createUuid();
}

CMessageResponse::CMessageResponse(const CMessageResponse &src)
{
    if (this != &src) copy(src);
}

CMessageResponse::CMessageResponse(const CMessageRequest &src)
{
    m_id = src.getId();
    m_strSenderId = src.getSenderId();
    m_strMsgUuid = src.getMsgUuid();
}

CMessageResponse &CMessageResponse::operator=(const CMessageResponse &src)
{
    if (this != &src) copy(src);
    return *this;
}

void CMessageResponse::copy(const CMessageResponse &src)
{
    m_id = src.m_id;
    m_code = src.m_code;
    m_strErrMsg = src.m_strErrMsg;
    m_result = src.m_result;

    m_strSenderId = src.m_strSenderId;
    m_strMsgUuid = src.m_strMsgUuid;
}

bool CMessageResponse::fromJson(const QJsonObject& obj)
{
    if (obj.contains("id") && obj["id"].isDouble())
    {
        setId(obj["id"].toVariant().toLongLong());
    }
    if (obj.contains("code") && obj["code"].isDouble())
    {
        setCode(obj["code"].toVariant().toLongLong());
    }
    if (obj.contains("errmsg") && obj["errmsg"].isString())
    {
        setErrMsg(obj["errmsg"].toString());
    }
    if (obj.contains("result") && obj["result"].isObject())
    {
        setResult(obj["result"].toObject());
    }

    if (obj.contains("senderId") && obj["senderId"].isString())
    {
        setSenderId(obj["senderId"].toString());
    }
    if (obj.contains("msgUuid") && obj["msgUuid"].isString())
    {
        setMsgUuid(obj["msgUuid"].toString());
    }
    if (obj.contains("isPrintLog") && obj["isPrintLog"].isBool())
    {
        setPrintLog(obj["isPrintLog"].toBool());
    }

    return true;
}

QJsonObject CMessageResponse::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("id",getId());
    obj.insert("code",getCode());
    obj.insert("errmsg",getErrMsg());
    obj.insert("result", getResult());

    obj.insert("senderId",getSenderId());
    obj.insert("msgUuid",getMsgUuid());
    obj.insert("isPrintLog",isPrintLog());

    return obj;
}

QJsonObject CMessageResponse::toJsonObjectSimple() const
{
    QJsonObject obj;
    obj.insert("id",getId());
    obj.insert("code",getCode());
    obj.insert("errmsg",getErrMsg());
    obj.insert("result", getResult());

    return obj;
}

QString CMessageResponse::toJsonStringSimple() const
{
    QJsonDocument doc(toJsonObjectSimple());
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
bool getParamsValue(const QJsonValue& obj, const QString& strKey, bool defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isBool())
    {
        return o[strKey].toBool();
    }
    return defaultValue;
}
int getParamsValue(const QJsonValue& obj, const QString& strKey, int defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isDouble())
    {
        return o[strKey].toInt();
    }
    return defaultValue;
}
unsigned int getParamsValue(const QJsonValue &obj, const QString &strKey, unsigned int defaultValue)
{
    return static_cast<unsigned int>(getParamsValue(obj, strKey, static_cast<int>(defaultValue)));
}
double getParamsValue(const QJsonValue& obj, const QString& strKey, double defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isDouble())
    {
        return o[strKey].toDouble();
    }
    return defaultValue;
}
QString getParamsValue(const QJsonValue& obj, const QString& strKey, QString defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isString())
    {
        return o[strKey].toString();
    }
    return defaultValue;
}
QJsonObject getParamsValue(const QJsonValue& obj, const QString& strKey, QJsonObject defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isObject())
    {
        return o[strKey].toObject();
    }
    return defaultValue;
}
QJsonArray getParamsValue(const QJsonValue& obj, const QString& strKey, QJsonArray defaultValue)
{
    if (!obj.isObject()) return defaultValue;
    QJsonObject o = obj.toObject();
    if (o.contains(strKey) && o[strKey].isArray())
    {
        return o[strKey].toArray();
    }
    return defaultValue;
}
void setParamsValue(QJsonValue& obj, const QString& strKey, const QJsonValue& newValue)
{
    if (!obj.isObject()) return;
    QJsonObject o = obj.toObject();
    o.insert(strKey, newValue);
    obj = o;
}
