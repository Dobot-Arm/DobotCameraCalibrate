#include "GetInfoListBean.h"

bool CGetInfoListRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    directory = obj["directory"].toString();
    type = obj["type"].toString();
    return true;
}

QJsonObject CGetInfoListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("directory",directory);
    obj.insert("type",type);
    return obj;
}

bool CGetInfoListRequestParams::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CGetInfoListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetInfoListBean::fromJson(const QJsonObject &obj)
{
    name = obj["name"].toString();
    type = obj["type"].toString();
    size = obj["size"].toVariant().toLongLong();
    return true;
}

QJsonObject CGetInfoListBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("name",name);
    obj.insert("type",type);
    obj.insert("size",size);
    return obj;
}

bool CGetInfoListResponseResult::fromJson(const QJsonObject &obj)
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
            CGetInfoListBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetInfoListResponseResult::toJsonObject() const
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
