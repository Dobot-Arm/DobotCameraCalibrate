#include "TakeBasePhotoBean.h"

bool CTakeBasePhotoRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("savePath") && obj["savePath"].isString()) savePath = obj["savePath"].toString();
    if (obj.contains("returnFrame") && obj["returnFrame"].isBool()) returnFrame = obj["returnFrame"].toBool();
    if (obj.contains("returnResult") && obj["returnResult"].isBool()) returnResult = obj["returnResult"].toBool();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CTakeBasePhotoRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("savePath",savePath);
    obj.insert("returnFrame",returnFrame);
    obj.insert("returnResult",returnResult);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CTakeBasePhotoRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CTakeBasePhotoRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CTakeBasePhotoResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("frame") && obj["frame"].isString()) frame = obj["frame"].toString();
    if (obj.contains("width") && obj["width"].isDouble()) width = obj["width"].toInt();
    if (obj.contains("height") && obj["height"].isDouble()) height = obj["height"].toInt();
    if (obj.contains("result") && obj["result"].isObject()) result.fromJson(obj["result"].toObject());
    return true;
}

QJsonObject CTakeBasePhotoResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("fileName",fileName);
    obj.insert("frame",frame);
    obj.insert("width",width);
    obj.insert("height",height);
    obj.insert("result", result.toJsonObject());
    return obj;
}

bool CTakeBasePhotoResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CTakeBasePhotoResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
