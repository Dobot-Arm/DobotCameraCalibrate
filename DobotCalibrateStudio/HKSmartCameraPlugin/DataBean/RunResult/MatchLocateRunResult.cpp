#include "MatchLocateRunResult.h"

bool MatchLocateRunResult::fromJson(const QJsonObject &obj)
{
    QJsonArray arrData = obj["data"].toArray();
    for (int i=0; i<arrData.size(); ++i)
    {
        QJsonObject codeObj = arrData.at(i).toObject();

        MatchLocateRunResult::DataResult code;
        code.precision = codeObj["precision"].toDouble();
        code.physicalX = codeObj["physicalX"].toDouble();
        code.physicalY = codeObj["physicalY"].toDouble();
        code.physicalAng = codeObj["physicalAng"].toDouble();
        code.offsetX = codeObj["offsetX"].toDouble();
        code.offsetY = codeObj["offsetY"].toDouble();
        code.offsetTheta = codeObj["offsetTheta"].toDouble();
        code.matchCenterX = codeObj["matchCenterX"].toDouble();
        code.matchCenterY = codeObj["matchCenterY"].toDouble();
        code.matchCenterWidth = codeObj["matchCenterWidth"].toDouble();
        code.matchCenterHeight = codeObj["matchCenterHeight"].toDouble();
        code.matchCenterAng = codeObj["matchCenterAng"].toDouble();

        data.push_back(code);
    }

    return true;
}

QJsonObject MatchLocateRunResult::toJsonObject() const
{
    QJsonObject obj;
    QJsonArray arrData;
    for (int i=0; i<data.size(); ++i)
    {
        const auto& code = data.at(i);
        QJsonObject codeObj;
        codeObj.insert("precision",code.precision);
        codeObj.insert("physicalX",code.physicalX);
        codeObj.insert("physicalY",code.physicalY);
        codeObj.insert("physicalAng",code.physicalAng);
        codeObj.insert("offsetX",code.offsetX);
        codeObj.insert("offsetY",code.offsetY);
        codeObj.insert("offsetTheta",code.offsetTheta);
        codeObj.insert("matchCenterX",code.matchCenterX);
        codeObj.insert("matchCenterY",code.matchCenterY);
        codeObj.insert("matchCenterWidth",code.matchCenterWidth);
        codeObj.insert("matchCenterHeight",code.matchCenterHeight);
        codeObj.insert("matchCenterAng",code.matchCenterAng);
        arrData.append(codeObj);
    }
    obj.insert("data",arrData);

    return obj;
}
