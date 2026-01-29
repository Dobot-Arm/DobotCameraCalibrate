#include "ReuseTransform.h"

bool CReuseTransformBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("x") && obj["x"].isDouble()) x = obj["x"].toDouble();
    if (obj.contains("y") && obj["y"].isDouble()) y = obj["y"].toDouble();
    if (obj.contains("z") && obj["z"].isDouble()) z = obj["z"].toDouble();
    if (obj.contains("rx") && obj["rx"].isDouble()) rx = obj["rx"].toDouble();
    if (obj.contains("ry") && obj["ry"].isDouble()) ry = obj["ry"].toDouble();
    if (obj.contains("rz") && obj["rz"].isDouble()) rz = obj["rz"].toDouble();

    return true;
}

QJsonObject CReuseTransformBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("x",x);
    obj.insert("y",y);
    obj.insert("z",z);
    obj.insert("rx",rx);
    obj.insert("ry",ry);
    obj.insert("rz",rz);
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CToolTransformationRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("oldPoint") && obj["oldPoint"].isObject())
    {
        oldPoint.fromJson(obj["oldPoint"].toObject());
    }
    if (obj.contains("newPoint") && obj["newPoint"].isObject())
    {
        newPoint.fromJson(obj["newPoint"].toObject());
    }

    return true;
}

QJsonObject CToolTransformationRequestBean::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("oldPoint", oldPoint.toJsonObject());
    obj.insert("newPoint", newPoint.toJsonObject());
    return obj;
}

bool CToolTransformationRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CToolTransformationRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
bool CToolTransformationResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isDouble()) continue;
            m_data.append(itr->toDouble());
        }
    }

    return true;
}

QJsonObject CToolTransformationResultResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(*itr);
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}
/*********************************************************************************************************/
/*********************************************************************************************************/
bool CAxisTransformationRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("oldPoints") && obj["oldPoints"].isArray())
    {
        QJsonArray arr = obj["oldPoints"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject()) continue;
            CReuseTransformBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                oldPoints.append(bean);
            }
        }
    }
    if (obj.contains("newPoints") && obj["newPoints"].isArray())
    {
        QJsonArray arr = obj["newPoints"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isObject()) continue;
            CReuseTransformBean bean;
            if (bean.fromJson(itr->toObject()))
            {
                newPoints.append(bean);
            }
        }
    }

    return true;
}

QJsonObject CAxisTransformationRequestBean::toJsonObject() const
{
    QJsonArray oldArray;
    for(auto itr=oldPoints.begin(); itr != oldPoints.end(); ++itr)
    {
        oldArray.append(itr->toJsonObject());
    }
    QJsonArray newArray;
    for(auto itr=newPoints.begin(); itr != newPoints.end(); ++itr)
    {
        newArray.append(itr->toJsonObject());
    }

    QJsonObject obj;
    obj.insert("oldPoints", oldArray);
    obj.insert("newPoints", newArray);
    return obj;
}

bool CAxisTransformationRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CAxisTransformationRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
bool CAxisTransformationResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isArray())
    {
        QJsonArray arr = obj["data"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isDouble()) continue;
            m_data.append(itr->toDouble());
        }
    }

    return true;
}

QJsonObject CAxisTransformationResultResponseResult::toJsonObject() const
{
    QJsonArray dataArray;
    for(auto itr=m_data.begin(); itr != m_data.end(); ++itr)
    {
        dataArray.append(*itr);
    }

    QJsonObject obj;
    obj.insert("data", dataArray);
    return obj;
}

/*********************************************************************************************************/
/*********************************************************************************************************/
bool CReusePointRequestBean::fromJson(const QJsonObject &obj)
{
    if (obj.contains("srcPoint") && obj["srcPoint"].isObject())
    {
        srcPoint.fromJson(obj["srcPoint"].toObject());
    }
    if (obj.contains("toolRT") && obj["toolRT"].isArray())
    {
        QJsonArray arr = obj["toolRT"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isDouble()) continue;
            toolRT.append(itr->toDouble());
        }
    }
    if (obj.contains("coordRT") && obj["coordRT"].isArray())
    {
        QJsonArray arr = obj["coordRT"].toArray();
        for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
        {
            if (!itr->isDouble()) continue;
            coordRT.append(itr->toDouble());
        }
    }

    return true;
}

QJsonObject CReusePointRequestBean::toJsonObject() const
{
    QJsonArray rt1;
    for(auto itr=toolRT.begin(); itr != toolRT.end(); ++itr)
    {
        rt1.append(*itr);
    }
    QJsonArray rt2;
    for(auto itr=coordRT.begin(); itr != coordRT.end(); ++itr)
    {
        rt2.append(*itr);
    }

    QJsonObject obj;
    obj.insert("srcPoint", srcPoint.toJsonObject());
    obj.insert("toolRT", rt1);
    obj.insert("coordRT", rt2);
    return obj;
}

bool CReusePointRequestParams::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        m_data.fromJson(obj["data"].toObject());
    }

    return true;
}

QJsonObject CReusePointRequestParams::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("data", m_data.toJsonObject());
    return obj;
}
/*********************************************************************************************************/
bool CReusePointResultResponseResult::fromJson(const QJsonObject &obj)
{
    if (obj.contains("data") && obj["data"].isObject())
    {
        QJsonObject data = obj["data"].toObject();
        m_data.x = data["x"].toDouble();
        m_data.y = data["y"].toDouble();
        m_data.z = data["z"].toDouble();
        m_data.rx = data["rx"].toDouble();
        m_data.ry = data["ry"].toDouble();
        m_data.rz = data["rz"].toDouble();
    }

    return true;
}

QJsonObject CReusePointResultResponseResult::toJsonObject() const
{
    QJsonObject data;
    data.insert("x",m_data.x);
    data.insert("y",m_data.y);
    data.insert("z",m_data.z);
    data.insert("rx",m_data.rx);
    data.insert("ry",m_data.ry);
    data.insert("rz",m_data.rz);

    QJsonObject obj;
    obj.insert("data", data);
    return obj;
}
