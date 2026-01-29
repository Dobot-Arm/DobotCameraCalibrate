#include "SpeckleExistRunResult.h"

bool SpeckleExistRunResult::fromJson(const QJsonObject &obj)
{
    QJsonObject boxArea = obj["boxArea"].toObject();
    {
        this->boxArea.centerX = boxArea["centerX"].toDouble();
        this->boxArea.centerY = boxArea["centerY"].toDouble();
        this->boxArea.width = boxArea["width"].toDouble();
        this->boxArea.height = boxArea["height"].toDouble();
        this->boxArea.angle = boxArea["angle"].toDouble();
    }
    QJsonObject blobArea = obj["blobArea"].toObject();
    {
        this->blobArea.centerX = blobArea["centerX"].toDouble();
        this->blobArea.centerY = blobArea["centerY"].toDouble();
        this->blobArea.width = blobArea["width"].toDouble();
        this->blobArea.height = blobArea["height"].toDouble();
        this->blobArea.angle = blobArea["angle"].toDouble();
    }

    this->area = obj["area"].toDouble();
    this->centroidX = obj["centroidX"].toDouble();
    this->centroidY = obj["centroidY"].toDouble();
    this->frame = obj["frame"].toString();
    this->width = obj["width"].toInt();
    this->height = obj["height"].toInt();
    this->fixtureRunPointX = obj["fixtureRunPointX"].toDouble();
    this->fixtureRunPointY = obj["fixtureRunPointY"].toDouble();
    this->fixtureRunAngle = obj["fixtureRunAngle"].toDouble();

    return true;
}

QJsonObject SpeckleExistRunResult::toJsonObject() const
{
    QJsonObject boxArea;
    {
        boxArea.insert("centerX",this->boxArea.centerX);
        boxArea.insert("centerY",this->boxArea.centerY);
        boxArea.insert("width",this->boxArea.width);
        boxArea.insert("height",this->boxArea.height);
        boxArea.insert("angle",this->boxArea.angle);
    }

    QJsonObject blobArea;
    {
        blobArea.insert("centerX",this->blobArea.centerX);
        blobArea.insert("centerY",this->blobArea.centerY);
        blobArea.insert("width",this->blobArea.width);
        blobArea.insert("height",this->blobArea.height);
        blobArea.insert("angle",this->blobArea.angle);
    }

    QJsonObject obj;
    obj.insert("boxArea",boxArea);
    obj.insert("blobArea",blobArea);
    obj.insert("area",this->area);
    obj.insert("centroidX",this->centroidX);
    obj.insert("centroidY",this->centroidY);
    obj.insert("fixtureRunPointX",this->fixtureRunPointX);
    obj.insert("fixtureRunPointY",this->fixtureRunPointY);
    obj.insert("fixtureRunAngle",this->fixtureRunAngle);
    obj.insert("frame",frame);
    obj.insert("width",width);
    obj.insert("height",height);
    return obj;
}
