#include "DlocrDetectRunResult.h"

bool DlocrDetectRunResult::fromJson(const QJsonObject &obj)
{
    charLimitDown = obj["charLimitDown"].toInt();
    charLimitUp = obj["charLimitUp"].toInt();
    QJsonArray arr = obj["codeValues"].toArray();
    for (int i=0; i<arr.size(); ++i)
    {
        QJsonObject codeObj = arr.at(i).toObject();

        DlocrDetectRunResult::CharValues code;

        code.status = codeObj["status"].toBool();
        code.content = codeObj["content"].toString();
        code.score = codeObj["score"].toDouble();

        QJsonObject boxArea = codeObj["boxArea"].toObject();
        code.boxArea.centerX = boxArea["centerX"].toDouble();
        code.boxArea.centerY = boxArea["centerY"].toDouble();
        code.boxArea.width = boxArea["width"].toDouble();
        code.boxArea.height = boxArea["height"].toDouble();
        code.boxArea.angle = boxArea["angle"].toDouble();

        QJsonObject scoreShowArea = codeObj["scoreShowArea"].toObject();
        code.scoreShowArea.x = scoreShowArea["x"].toDouble();
        code.scoreShowArea.y = scoreShowArea["y"].toDouble();
        code.scoreShowArea.angle = scoreShowArea["angle"].toDouble();

        QJsonObject contentShowArea = codeObj["contentShowArea"].toObject();
        code.contentShowArea.x = contentShowArea["x"].toDouble();
        code.contentShowArea.y = contentShowArea["y"].toDouble();
        code.contentShowArea.angle = contentShowArea["angle"].toDouble();

        charValues.push_back(code);
    }
    return true;
}

QJsonObject DlocrDetectRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("charLimitDown",charLimitDown);
    obj.insert("charLimitUp",charLimitUp);
    QJsonArray arrCodeValues;
    for (int i=0; i<charValues.size(); ++i)
    {
        auto& codeV = charValues[i];
        QJsonObject codeObj;
        codeObj.insert("status",codeV.status);
        codeObj.insert("content",codeV.content);
        codeObj.insert("score",codeV.score);

        QJsonObject boxArea;
        {
            boxArea.insert("centerX",codeV.boxArea.centerX);
            boxArea.insert("centerY",codeV.boxArea.centerY);
            boxArea.insert("width",codeV.boxArea.width);
            boxArea.insert("height",codeV.boxArea.height);
            boxArea.insert("angle",codeV.boxArea.angle);
        }
        codeObj.insert("boxArea",boxArea);

        QJsonObject scoreShowArea;
        {
            scoreShowArea.insert("centerX",codeV.scoreShowArea.x);
            scoreShowArea.insert("centerY",codeV.scoreShowArea.y);
            scoreShowArea.insert("width",codeV.scoreShowArea.angle);
        }
        codeObj.insert("scoreShowArea",scoreShowArea);

        QJsonObject contentShowArea;
        {
            contentShowArea.insert("centerX",codeV.contentShowArea.x);
            contentShowArea.insert("centerY",codeV.contentShowArea.y);
            contentShowArea.insert("width",codeV.contentShowArea.angle);
        }
        codeObj.insert("contentShowArea",contentShowArea);

        arrCodeValues.append(codeObj);
    }
    obj.insert("codeValues",arrCodeValues);
    return obj;
}
