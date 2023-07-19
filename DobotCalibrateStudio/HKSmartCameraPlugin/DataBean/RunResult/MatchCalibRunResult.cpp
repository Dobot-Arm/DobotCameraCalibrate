#include "MatchCalibRunResult.h"

bool MatchCalibRunResult::fromJson(const QJsonObject &obj)
{
    transformDelta = obj["transformDelta"].toDouble();
    rotationDelta = obj["rotationDelta"].toDouble();
    score = obj["score"].toDouble();
    progress = obj["progress"].toString();

    QJsonObject matchBoxObj = obj["matchBox"].toObject();
    matchBox.centerX = matchBoxObj["centerX"].toDouble();
    matchBox.centerY = matchBoxObj["centerY"].toDouble();
    matchBox.width = matchBoxObj["width"].toDouble();
    matchBox.height = matchBoxObj["height"].toDouble();
    matchBox.angle = matchBoxObj["angle"].toDouble();

    QJsonObject matchPointObj = obj["matchPoint"].toObject();
    matchPoint.x = matchPointObj["x"].toDouble();
    matchPoint.y = matchPointObj["y"].toDouble();

    QJsonArray arrOutputPoints = obj["outputPoints"].toArray();
    for (int i=0; i<arrOutputPoints.size(); ++i)
    {
        QJsonObject codeObj = arrOutputPoints.at(i).toObject();

        MatchCalibRunResult::OutputPoint code;
        code.imageX = obj["imageX"].toDouble();
        code.imageY = obj["imageY"].toDouble();
        code.physicalX = obj["physicalX"].toDouble();
        code.physicalY = obj["physicalY"].toDouble();
        code.angle = obj["angle"].toDouble();

        outputPoints.push_back(code);
    }
    return true;
}

QJsonObject MatchCalibRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("transformDelta", transformDelta);
    obj.insert("rotationDelta", rotationDelta);
    obj.insert("score", score);
    obj.insert("progress", progress);

    QJsonObject matchBoxObj;
    {
        matchBoxObj.insert("centerX",matchBox.centerX);
        matchBoxObj.insert("centerY",matchBox.centerY);
        matchBoxObj.insert("width",matchBox.width);
        matchBoxObj.insert("height",matchBox.height);
        matchBoxObj.insert("angle",matchBox.angle);
    }
    obj.insert("matchBox",matchBoxObj);

    QJsonObject matchPointObj;
    {
        matchPointObj.insert("x",matchPoint.x);
        matchPointObj.insert("y",matchPoint.y);
    }
    obj.insert("matchPoint",matchPointObj);

    QJsonArray arrOutputPoints;
    for (int i=0; i<outputPoints.size(); ++i)
    {
        const auto& code = outputPoints.at(i);
        QJsonObject codeObj;
        codeObj.insert("imageX", code.imageX);
        codeObj.insert("imageY", code.imageY);
        codeObj.insert("physicalX", code.physicalX);
        codeObj.insert("physicalY", code.physicalY);
        codeObj.insert("angle", code.angle);
        arrOutputPoints.append(codeObj);
    }
    obj.insert("outputPoints",arrOutputPoints);

    return obj;
}
