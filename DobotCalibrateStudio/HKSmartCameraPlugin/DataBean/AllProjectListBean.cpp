#include "AllProjectListBean.h"

bool CAllProjectListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    return true;
}

QJsonObject CAllProjectListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    return obj;
}

bool CAllProjectListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CAllProjectListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}


/*********************************************************************************************************/
/*********************************************************************************************************/
bool CAllProjectListResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("name") && obj["name"].isString()) name = obj["name"].toString();
    if (obj.contains("createDateTime") && obj["createDateTime"].isString()) createDateTime = obj["createDateTime"].toString();
    if (obj.contains("baseImageName") && obj["baseImageName"].isString()) baseImageName = obj["baseImageName"].toString();
    return true;
}

QJsonObject CAllProjectListResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("name",name);
    obj.insert("createDateTime",createDateTime);
    obj.insert("baseImageName",baseImageName);
    return obj;
}

bool CAllProjectListResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("name") && obj["name"].isString()) name = obj["name"].toString();
    if (obj.contains("all") && obj["all"].isArray())
    {
        QJsonArray arr = obj["all"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CAllProjectListResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                all.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CAllProjectListResponseBean2::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=all.begin(); itr != all.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("name", name);
    obj.insert("all", dataArray);
    return obj;
}

bool CAllProjectListResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CAllProjectListResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
