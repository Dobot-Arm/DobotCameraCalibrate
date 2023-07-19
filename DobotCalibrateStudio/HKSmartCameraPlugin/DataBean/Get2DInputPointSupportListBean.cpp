#include "Get2DInputPointSupportListBean.h"

bool CGet2DInputPointSupportListRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("identify") && obj["identify"].isString()) identify = obj["identify"].toString();
    if (obj.contains("saveDbgFile") && obj["saveDbgFile"].isBool()) isSaveDbgFile = obj["saveDbgFile"].toBool();
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    return true;
}

QJsonObject CGet2DInputPointSupportListRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("identify", identify);
    obj.insert("saveDbgFile", isSaveDbgFile);
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    return obj;
}

bool CGet2DInputPointSupportListRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGet2DInputPointSupportListRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CGet2DInputPointSupportListResponseBean1::fromJson(const QJsonObject &obj)
{
    if (obj.contains("paramName") && obj["paramName"].isString()) paramName = obj["paramName"].toString();
    if (obj.contains("paramNameCN") && obj["paramNameCN"].isString()) paramNameCN = obj["paramNameCN"].toString();
    if (obj.contains("paramNameEN") && obj["paramNameEN"].isString()) paramNameEN = obj["paramNameEN"].toString();
    return true;
}

QJsonObject CGet2DInputPointSupportListResponseBean1::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("paramName", paramName);
    obj.insert("paramNameCN", paramNameCN);
    obj.insert("paramNameEN", paramNameEN);
    return obj;
}

bool CGet2DInputPointSupportListResponseBean2::fromJson(const QJsonObject &obj)
{
    if (obj.contains("moduleName") && obj["moduleName"].isString()) moduleName = obj["moduleName"].toString();
    if (obj.contains("moduleId") && obj["moduleId"].isDouble()) moduleId = obj["moduleId"].toInt();
    if (obj.contains("displayNameCN") && obj["displayNameCN"].isString()) displayNameCN = obj["displayNameCN"].toString();
    if (obj.contains("displayNameEN") && obj["displayNameEN"].isString()) displayNameEN = obj["displayNameEN"].toString();
    QJsonArray subParamListArr = obj["subParamList"].toArray();
    for (int i=0; i<subParamListArr.size(); ++i)
    {
        if (subParamListArr[i].isObject())
        {
            CGet2DInputPointSupportListResponseBean1 bean;
            bean.fromJson(subParamListArr[i].toObject());
            subParamList.append(bean);
        }
    }
    return true;
}

QJsonObject CGet2DInputPointSupportListResponseBean2::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("moduleName", moduleName);
    obj.insert("moduleId", moduleId);
    obj.insert("displayNameCN", displayNameCN);
    obj.insert("displayNameEN", displayNameEN);
    QJsonArray subParamListArr;
    for (int i=0; i<subParamList.size(); ++i)
    {
        subParamListArr.append(subParamList[i].toJsonObject());
    }
    obj.insert("subParamList", subParamListArr);
    return obj;
}

bool CGet2DInputPointSupportListResponseBean3::fromJson(const QJsonObject &obj)
{
    QJsonArray runPointXArr = obj["runPointX"].toArray();
    QJsonArray runPointYArr = obj["runPointY"].toArray();
    QJsonArray runPointAngleArr = obj["runPointAngle"].toArray();

    for (int i=0; i<runPointXArr.size(); ++i)
    {
        if (runPointXArr[i].isObject())
        {
            CGet2DInputPointSupportListResponseBean2 bean;
            bean.fromJson(runPointXArr[i].toObject());
            runPointX.append(bean);
        }
    }
    for (int i=0; i<runPointYArr.size(); ++i)
    {
        if (runPointYArr[i].isObject())
        {
            CGet2DInputPointSupportListResponseBean2 bean;
            bean.fromJson(runPointYArr[i].toObject());
            runPointY.append(bean);
        }
    }
    for (int i=0; i<runPointAngleArr.size(); ++i)
    {
        if (runPointAngleArr[i].isObject())
        {
            CGet2DInputPointSupportListResponseBean2 bean;
            bean.fromJson(runPointAngleArr[i].toObject());
            runPointAngle.append(bean);
        }
    }

    return true;
}

QJsonObject CGet2DInputPointSupportListResponseBean3::toJsonObject() const
{
    QJsonObject obj;
    QJsonArray runPointXArr;
    for (int i=0; i<runPointX.size(); ++i)
    {
        runPointXArr.append(runPointX[i].toJsonObject());
    }
    obj.insert("runPointX", runPointXArr);

    QJsonArray runPointYArr;
    for (int i=0; i<runPointY.size(); ++i)
    {
        runPointYArr.append(runPointY[i].toJsonObject());
    }
    obj.insert("runPointY", runPointYArr);

    QJsonArray runPointAngleArr;
    for (int i=0; i<runPointAngle.size(); ++i)
    {
        runPointAngleArr.append(runPointAngle[i].toJsonObject());
    }
    obj.insert("runPointAngle", runPointAngleArr);

    return obj;
}

bool CGet2DInputPointSupportListResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }
    return true;
}

QJsonObject CGet2DInputPointSupportListResponseResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
