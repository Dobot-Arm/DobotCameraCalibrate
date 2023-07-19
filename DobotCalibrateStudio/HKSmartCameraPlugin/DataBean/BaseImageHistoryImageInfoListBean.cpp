#include "BaseImageHistoryImageInfoListBean.h"

bool CBaseImageHistoryImageInfoListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isDouble()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CBaseImageHistoryImageInfoListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CBaseImageHistoryImageInfoListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CBaseImageHistoryImageInfoListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CBaseImageHistoryImageInfoListResponseBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("imageName") && obj["imageName"].isString()) imageName = obj["imageName"].toString();
    if (obj.contains("imageDate") && obj["imageDate"].isString()) imageDate = obj["imageDate"].toString();
    if (obj.contains("imageState") && obj["imageState"].isBool()) imageState = obj["imageState"].toBool();
    return true;
}

QJsonObject CBaseImageHistoryImageInfoListResponseBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("imageName",imageName);
    obj.insert("imageDate",imageDate);
    obj.insert("imageState",imageState);
    return obj;
}

bool CBaseImageHistoryImageInfoListResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject())
            {
                continue;
            }
            CBaseImageHistoryImageInfoListResponseBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CBaseImageHistoryImageInfoListResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}
