#include "TakePhotoBean.h"

bool CTakePhotoRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("savePath") && obj["savePath"].isString()) savePath = obj["savePath"].toString();
    return true;
}

QJsonObject CTakePhotoRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("savePath",savePath);
    return obj;
}

bool CTakePhotoRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CTakePhotoRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CTakePhotoResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("fileName") && obj["fileName"].isString()) fileName = obj["fileName"].toString();
    if (obj.contains("frame") && obj["frame"].isString()) frame = obj["frame"].toString();
    return true;
}

QJsonObject CTakePhotoResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("fileName",fileName);
    obj.insert("frame",frame);
    return obj;
}

bool CTakePhotoResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CTakePhotoResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
