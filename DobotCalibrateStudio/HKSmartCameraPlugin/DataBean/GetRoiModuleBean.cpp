#include "GetRoiModuleBean.h"

bool CGetRoiModuleRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGetRoiModuleRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGetRoiModuleRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGetRoiModuleRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGetRoiModuleResponseBean::fromJson(const QJsonObject &obj)
{
    for (auto itr=obj.begin(); itr!=obj.end(); ++itr)
    {
        if (UnknowRoiData::isMine(itr.key())) continue;

        QList<std::shared_ptr<BaseRoiData>> datas;
        QJsonArray arr = itr.value().toArray();
        for (int i=0; i<arr.size(); ++i)
        {
            if (!arr[i].isObject())
            {
                continue;
            }
            auto ptr = BaseRoiData::createBase(itr.key());
            if (ptr->fromJson(arr[i].toObject()))
            {
                datas.append(ptr);
            }
        }
        roi.insert(itr.key(), datas);
    }
    return true;
}

QJsonObject CGetRoiModuleResponseBean::toJsonObject() const
{
    QJsonObject obj;
    for(auto itr=roi.begin(); itr!=roi.end(); ++itr)
    {
        QJsonArray arr;
        for (auto itrArr=itr.value().begin(); itrArr!=itr.value().end(); ++itrArr)
        {
            arr.append(itrArr->get()->toJsonObject());
        }
        obj.insert(itr.key(),arr);
    }
    return obj;
}

bool CGetRoiModuleResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CGetRoiModuleResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
