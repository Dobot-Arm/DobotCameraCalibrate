#include "SpeckleCountRunResult.h"

bool SpeckleCountRunResult::fromJson(const QJsonObject &obj)
{
    frame = obj["frame"].toString();
    width = obj["width"].toInt();
    height = obj["height"].toInt();

    QJsonArray arr = obj["boxArea"].toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        QJsonObject boxAreaObj = arr.at(i).toObject();

        SpeckleCountRunResult::BoxArea beanResult;
        beanResult.centerX = boxAreaObj["centerX"].toDouble();
        beanResult.centerY = boxAreaObj["centerY"].toDouble();
        beanResult.width = boxAreaObj["width"].toDouble();
        beanResult.height = boxAreaObj["height"].toDouble();
        beanResult.angle = boxAreaObj["angle"].toDouble();

        this->boxArea.push_back(beanResult);
    }

    arr = obj["blobArea"].toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        QJsonObject matchResultObj = arr.at(i).toObject();

        SpeckleCountRunResult::BlobAreaResult beanResult;
        beanResult.centerX = matchResultObj["centerX"].toDouble();
        beanResult.centerY = matchResultObj["centerY"].toDouble();
        beanResult.width = matchResultObj["width"].toDouble();
        beanResult.height = matchResultObj["height"].toDouble();
        beanResult.angle = matchResultObj["angle"].toDouble();
        beanResult.area = matchResultObj["area"].toDouble();
        beanResult.centroidX = matchResultObj["centroidX"].toDouble();
        beanResult.centroidY = matchResultObj["centroidY"].toDouble();

        this->blobArea.push_back(beanResult);
    }
    return true;
}

QJsonObject SpeckleCountRunResult::toJsonObject() const
{

    QJsonArray arrBoxArea;
    for (int i=0; i<this->boxArea.size(); ++i)
    {
        auto& result = this->boxArea[i];
        QJsonObject boxObj;
        boxObj.insert("centerX",result.centerX);
        boxObj.insert("centerY",result.centerY);
        boxObj.insert("width",result.width);
        boxObj.insert("height",result.height);
        boxObj.insert("angle",result.angle);
        arrBoxArea.append(boxObj);
    }

    QJsonArray arrMatchResult;
    for (int i=0; i<this->blobArea.size(); ++i)
    {
        auto& result = this->blobArea[i];
        QJsonObject matchResultObj;
        matchResultObj.insert("centerX",result.centerX);
        matchResultObj.insert("centerY",result.centerY);
        matchResultObj.insert("width",result.width);
        matchResultObj.insert("height",result.height);
        matchResultObj.insert("angle",result.angle);
        matchResultObj.insert("area",result.area);
        matchResultObj.insert("centroidX",result.centroidX);
        matchResultObj.insert("centroidY",result.centroidY);
        arrMatchResult.append(matchResultObj);
    }

    QJsonObject obj;
    obj.insert("boxArea",arrBoxArea);
    obj.insert("matchResult",arrMatchResult);
    obj.insert("frame",frame);
    obj.insert("width",width);
    obj.insert("height",height);
    return obj;
}
