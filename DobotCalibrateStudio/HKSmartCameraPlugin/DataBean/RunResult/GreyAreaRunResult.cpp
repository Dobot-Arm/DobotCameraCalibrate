#include "GreyAreaRunResult.h"

bool GreyAreaRunResult::fromJson(const QJsonObject &obj)
{
    area = obj["area"].toDouble();
    limitDown = obj["limitDown"].toDouble();
    limitUp = obj["limitUp"].toDouble();

    QJsonObject boxAreaObj = obj["boxArea"].toObject();
    boxArea.centerX = boxAreaObj["centerX"].toDouble();
    boxArea.centerY = boxAreaObj["centerY"].toDouble();
    boxArea.width = boxAreaObj["width"].toDouble();
    boxArea.height = boxAreaObj["height"].toDouble();
    boxArea.angle = boxAreaObj["angle"].toDouble();

    QJsonObject showAreaObj = obj["areaShowArea"].toObject();
    areaShowArea.x = showAreaObj["x"].toDouble();
    areaShowArea.y = showAreaObj["y"].toDouble();
    areaShowArea.angle = showAreaObj["angle"].toDouble();

    frame = obj["frame"].toString();
    return true;
}

QJsonObject GreyAreaRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("area",area);
    obj.insert("limitDown",limitDown);
    obj.insert("limitUp",limitUp);

    QJsonObject boxAreaObj;
    boxAreaObj.insert("centerX",boxArea.centerX);
    boxAreaObj.insert("centerY",boxArea.centerY);
    boxAreaObj.insert("width",boxArea.width);
    boxAreaObj.insert("height",boxArea.height);
    boxAreaObj.insert("angle",boxArea.angle);
    obj.insert("boxArea",boxAreaObj);

    QJsonObject showAreaObj;
    showAreaObj.insert("x",areaShowArea.x);
    showAreaObj.insert("y",areaShowArea.y);
    showAreaObj.insert("angle",areaShowArea.angle);
    obj.insert("areaShowArea",showAreaObj);

    obj.insert("frame",frame);
    return obj;
}
