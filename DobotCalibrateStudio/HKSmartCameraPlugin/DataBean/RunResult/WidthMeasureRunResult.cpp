#include "WidthMeasureRunResult.h"

bool WidthMeasureRunResult::fromJson(const QJsonObject &obj)
{
    width = obj["width"].toDouble();
    limitDown = obj["limitDown"].toDouble();
    limitUp = obj["limitUp"].toDouble();
    showTextX = obj["showTextX"].toDouble();
    showTextY = obj["showTextY"].toDouble();
    showTextAng = obj["showTextAng"].toDouble();
    QJsonArray arrLines = obj["markLines"].toArray();
    for (int i=0; i<arrLines.size(); ++i)
    {
        QJsonObject lineObj = arrLines.at(i).toObject();
        if (lineObj.isEmpty()) continue;
        WidthMeasureRunResult::MarkLines line;
        line.startX = lineObj["startX"].toDouble();
        line.startY = lineObj["startY"].toDouble();
        line.endX = lineObj["endX"].toDouble();
        line.endY = lineObj["endY"].toDouble();
        line.angle = lineObj["angle"].toDouble();
        markLines.append(line);
    }
    return true;
}

QJsonObject WidthMeasureRunResult::toJsonObject() const
{
    QJsonObject obj;
    obj.insert("width",width);
    obj.insert("limitDown",limitDown);
    obj.insert("limitUp",limitUp);
    obj.insert("showTextX",showTextX);
    obj.insert("showTextY",showTextY);
    obj.insert("showTextAng",showTextAng);
    QJsonArray arrLines;
    for (int i=0; i<markLines.size(); ++i)
    {
        const auto& line = markLines.at(i);
        QJsonObject lineObj;
        lineObj.insert("startX",line.startX);
        lineObj.insert("startY",line.startY);
        lineObj.insert("endX",line.endX);
        lineObj.insert("endY",line.endY);
        lineObj.insert("angle",line.angle);
        arrLines.append(lineObj);
    }
    obj.insert("markLines",arrLines);
    return obj;
}
