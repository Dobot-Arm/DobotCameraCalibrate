#include "ImageCountRunResult.h"

bool ImageCountRunResult::fromJson(const QJsonObject &obj)
{
    QJsonObject boxArea = obj["boxArea"].toObject();
    {
        this->boxArea.centerX = boxArea["centerX"].toDouble();
        this->boxArea.centerY = boxArea["centerY"].toDouble();
        this->boxArea.width = boxArea["width"].toDouble();
        this->boxArea.height = boxArea["height"].toDouble();
        this->boxArea.angle = boxArea["angle"].toDouble();
    }

    QJsonArray arr = obj["matchResult"].toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        QJsonObject matchResultObj = arr.at(i).toObject();

        ImageCountRunResult::MatchResult beanResult;
        beanResult.centerX = matchResultObj["centerX"].toDouble();
        beanResult.centerY = matchResultObj["centerY"].toDouble();
        beanResult.width = matchResultObj["width"].toDouble();
        beanResult.height = matchResultObj["height"].toDouble();
        beanResult.angle = matchResultObj["angle"].toDouble();
        beanResult.score = matchResultObj["score"].toDouble();
        beanResult.matchX = matchResultObj["matchX"].toDouble();
        beanResult.matchY = matchResultObj["matchY"].toDouble();

        this->matchResult.push_back(beanResult);
    }
    return true;
}

QJsonObject ImageCountRunResult::toJsonObject() const
{
    QJsonObject boxArea;
    {
        boxArea.insert("centerX",this->boxArea.centerX);
        boxArea.insert("centerY",this->boxArea.centerY);
        boxArea.insert("width",this->boxArea.width);
        boxArea.insert("height",this->boxArea.height);
        boxArea.insert("angle",this->boxArea.angle);
    }

    QJsonArray arrMatchResult;
    for (int i=0; i<this->matchResult.size(); ++i)
    {
        auto& result = this->matchResult[i];
        QJsonObject matchResultObj;
        matchResultObj.insert("centerX",result.centerX);
        matchResultObj.insert("centerY",result.centerY);
        matchResultObj.insert("width",result.width);
        matchResultObj.insert("height",result.height);
        matchResultObj.insert("angle",result.angle);
        matchResultObj.insert("score",result.score);
        matchResultObj.insert("matchX",result.matchX);
        matchResultObj.insert("matchY",result.matchY);
        arrMatchResult.append(matchResultObj);
    }

    QJsonObject obj;
    obj.insert("boxArea",boxArea);
    obj.insert("matchResult",arrMatchResult);
    return obj;
}
