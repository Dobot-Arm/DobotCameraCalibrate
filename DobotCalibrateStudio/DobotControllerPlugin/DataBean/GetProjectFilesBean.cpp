#include "GetProjectFilesBean.h"

bool CGetProjectFilesRequestBean::fromJson(const QJsonObject &obj)
{
    ip = obj["ip"].toString();
    port = obj["port"].toInt(22);
    projectName = obj["projectName"].toString();
    return true;
}

QJsonObject CGetProjectFilesRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("ip",ip);
    obj.insert("port",port);
    obj.insert("projectName",projectName);
    return obj;
}

bool CGetProjectFilesRequestParams::fromJson(const QJsonObject &obj)
{
    m_data.fromJson(obj["data"].toObject());
    return true;
}

QJsonObject CGetProjectFilesRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetProjectFilesBean::fromJson(const QJsonObject &obj)
{
    fileName = obj["fileName"].toString();
    return true;
}

QJsonObject CGetProjectFilesBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("fileName",fileName);
    return obj;
}

bool CGetProjectFilesResponseResult::fromJson(const QJsonObject &obj)
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
            CGetProjectFilesBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                m_data.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CGetProjectFilesResponseResult::toJsonObject() const
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
