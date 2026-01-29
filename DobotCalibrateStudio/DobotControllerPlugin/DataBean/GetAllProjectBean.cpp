#include "GetAllProjectBean.h"

bool CGetAllProjectRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    return true;
}

QJsonObject CGetAllProjectRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    return obj;
}

bool CGetAllProjectRequestParams::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CGetAllProjectRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetAllProjectBean::fromJson(const QJsonObject &obj)
{
    projectName = obj["projectName"].toString();
    return true;
}

QJsonObject CGetAllProjectBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("projectName",projectName);
    return obj;
}

bool CGetAllProjectResponseResult::fromJson(const QJsonObject &obj)
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
            CGetAllProjectBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetAllProjectResponseResult::toJsonObject() const
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
