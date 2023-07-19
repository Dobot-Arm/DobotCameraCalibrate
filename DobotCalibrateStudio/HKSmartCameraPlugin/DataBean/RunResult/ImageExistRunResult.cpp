#include "ImageExistRunResult.h"

bool ImageExistRunResult::fromJson(const QJsonObject &obj)
{
    QJsonObject mbO = obj["matchBox"].toObject();
    matchBox.centerX = mbO["centerX"].toDouble();
    matchBox.centerY = mbO["centerY"].toDouble();
    matchBox.width = mbO["width"].toDouble();
    matchBox.height = mbO["height"].toDouble();
    matchBox.angle = mbO["angle"].toDouble();
    matchX = obj["matchX"].toDouble();
    matchY = obj["matchY"].toDouble();
    matchAng = obj["matchAng"].toDouble();
    score = obj["score"].toDouble();
    return true;
}

QJsonObject ImageExistRunResult::toJsonObject() const
{
    QJsonObject obj;
    {
        QJsonObject mbO;
        mbO.insert("centerX",matchBox.centerX);
        mbO.insert("centerY",matchBox.centerY);
        mbO.insert("width",matchBox.width);
        mbO.insert("height",matchBox.height);
        mbO.insert("angle",matchBox.angle);
        obj.insert("matchBox",mbO);
    }
    obj.insert("matchX",matchX);
    obj.insert("matchY",matchY);
    obj.insert("matchAng",matchAng);
    obj.insert("score",score);
    return obj;
}
