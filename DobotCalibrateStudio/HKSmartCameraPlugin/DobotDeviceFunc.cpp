#include "DobotDevice.h"
#include <QVector>

template<class First>
First calcMaxValue(First first)
{
    return first;
}
template<class First, class Second>
First calcMaxValue(First first, Second second)
{
    return first>second?first:second;
}
template<class T, class... Args>
T calcMaxValue(T first, Args... args)
{
    return calcMaxValue(first, calcMaxValue(args...));
}

static struct RunResultTempData
{
    QString strResultRefCN;
    QString strResultRefEN;
}g_RunResultTempData;
static QString parsePInfo(const QJsonArray& arrPInfo, MacapriltagRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, ImageExistRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, DiameterMeasureRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, WidthMeasureRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, IdeModuleRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, DlocrDetectRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, GreyAreaRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, MatchCalibRunResult* pRunResult, const QImage& renderImage=QImage());
static QString parsePInfo(const QJsonArray& arrPInfo, MatchLocateRunResult* pRunResult, const QImage& renderImage=QImage());

void CDobotDevice::parseProjectRunResult(const QString &strResultInfo, const QHash<int,QImage>& renderImage,
                                         CGetProjectRunResultResponseBean2 &result)
{
    result.clear();

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strResultInfo.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"parseProjectRunResult:the string is not json object,"<<err.errorString();
        return ;
    }
    QJsonObject objResult = jsonDoc.object();
    result.solutionName = objResult["ScDeviceCurrentSolutionName"].toString();
    result.totalNumber = objResult["ScDeviceSolutionTotalNumber"].toInt();
    result.ngNumber = objResult["ScDeviceSolutionNgNumber"].toInt();
    result.result = objResult["ScDeviceSolutionRunningResult"].toInt(1)==0 ? "OK":"NG"; //0表示整个方案是OK的

    QJsonArray currentDataArr = objResult["CurrentData"].toArray();
    for (int i=0; i<currentDataArr.size(); ++i)
    {
        if (!currentDataArr[i].isObject()) continue;

        QJsonObject curDataObj = currentDataArr[i].toObject();
        //int nStatus = curDataObj.value("nStatus").toInt(0); //算子模块流程运行的情况（正常运行无报错且有结果输出为1，否则为0）
        int iModuleId = curDataObj.value("nModuleID").toInt(0);
        QString strModuleName = curDataObj.value("ModuleName").toString();
        QJsonArray arrPInfo = curDataObj.value("pInfo").toArray();

        auto sptr = BaseRunResult::createBase(strModuleName);
        if (!sptr.get())
        {//说明module不是要处理的数据
            continue;
        }

        CGetProjectRunResultResponseBean bean;
        bean.moduleName = strModuleName;
        bean.moduleId = iModuleId;
        bean.result = "NG"; //默认给个NG，在内部计算判断
        bean.moduleData = sptr;
        if (MacapriltagRunResult::isMine(strModuleName))
        {//2.5D标定模块
            bean.result = parsePInfo(arrPInfo, (MacapriltagRunResult*)bean.moduleData.get());
        }
        else if (ImageExistRunResult::isMine(strModuleName))
        {//图像有无模块
            bean.result = parsePInfo(arrPInfo, (ImageExistRunResult*)bean.moduleData.get());
        }
        else if (DiameterMeasureRunResult::isMine(strModuleName))
        {//直径测量模块
            bean.result = parsePInfo(arrPInfo, (DiameterMeasureRunResult*)bean.moduleData.get());
        }
        else if (WidthMeasureRunResult::isMine(strModuleName))
        {//宽度测量模块
            bean.result = parsePInfo(arrPInfo, (WidthMeasureRunResult*)bean.moduleData.get());
        }
        else if (IdeModuleRunResult::isMine(strModuleName))
        {//码识别模块
            bean.result = parsePInfo(arrPInfo, (IdeModuleRunResult*)bean.moduleData.get());
        }
        else if (DlocrDetectRunResult::isMine(strModuleName))
        {//字符识别模块
            bean.result = parsePInfo(arrPInfo, (DlocrDetectRunResult*)bean.moduleData.get());
        }
        else if (GreyAreaRunResult::isMine(strModuleName))
        {//灰度面积模块
            bean.result = parsePInfo(arrPInfo, (GreyAreaRunResult*)bean.moduleData.get(),renderImage.value(iModuleId));
        }
        else if (MatchCalibRunResult::isMine(strModuleName))
        {//2D标定模块
            bean.result = parsePInfo(arrPInfo, (MatchCalibRunResult*)bean.moduleData.get());
        }
        else if (MatchLocateRunResult::isMine(strModuleName))
        {//2D定位
            bean.result = parsePInfo(arrPInfo, (MatchLocateRunResult*)bean.moduleData.get());
        }
        else
        {
            g_RunResultTempData.strResultRefCN = "";
            g_RunResultTempData.strResultRefEN = "";
        }
        bean.resultRefCN = g_RunResultTempData.strResultRefCN;
        bean.resultRefEN = g_RunResultTempData.strResultRefEN;
        result.data.append(bean);
    }
}

static QString parsePInfo(const QJsonArray& arrPInfo, MacapriltagRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;
    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_result_x" == strParamName || "SINGLE_result_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->x = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_y" == strParamName || "SINGLE_result_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->y = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_z" == strParamName || "SINGLE_result_z" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->z = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_a" == strParamName || "SINGLE_result_a" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->rx = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_b" == strParamName || "SINGLE_result_b" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->ry = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_c" == strParamName || "SINGLE_result_c" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->rz = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_result_ID" == strParamName || "SINGLE_result_ID" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            if (arrValue.size()>0) pRunResult->id = arrValue[0].toInt(0);
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, ImageExistRunResult *pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("BOX1_match_box_cx" == strParamName || "BOX1_match_box_cx" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.centerX = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_cy" == strParamName || "BOX1_match_box_cy" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.centerY = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_w" == strParamName || "BOX1_match_box_w" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.width = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_h" == strParamName || "BOX1_match_box_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.height = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_ang" == strParamName || "BOX1_match_box_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.angle = arrValue[0].toDouble(0);
            pRunResult->matchAng = pRunResult->matchBox.angle;
        }
        else if ("POINT_match_point_x" == strParamName || "POINT_match_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchX = arrValue[0].toDouble(0);
        }
        else if ("POINT_match_point_y" == strParamName || "POINT_match_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchY = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_match_score" == strParamName || "SINGLE_match_score" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->score = arrValue[0].toDouble(0);
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, DiameterMeasureRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;
    QVector<double> edgeOkX,edgeOkY,edgeNgX,edgeNgY;

    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("CIRCLE_circle_center_x" == strParamName || "CIRCLE_circle_center_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->centerX = arrValue[0].toDouble(0);
        }
        else if ("CIRCLE_circle_center_y" == strParamName || "CIRCLE_circle_center_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->centerY = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure" == strParamName || "SINGLE_rst_measure" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->diameter = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_l" == strParamName || "SINGLE_rst_measure_limit_l" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitDown = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_h" == strParamName || "SINGLE_rst_measure_limit_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitUp = arrValue[0].toDouble(0);
        }
        else if ("POINT_ok_edge_point_x" == strParamName || "POINT_ok_edge_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0; i<arrValue.size(); ++i) edgeOkX.push_back(arrValue[i].toDouble());
        }
        else if ("POINT_ok_edge_point_y" == strParamName || "POINT_ok_edge_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0; i<arrValue.size(); ++i) edgeOkY.push_back(arrValue[i].toDouble());
        }
        else if ("POINT_ng_edge_point_x" == strParamName || "POINT_ng_edge_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0; i<arrValue.size(); ++i) edgeNgX.push_back(arrValue[i].toDouble());
        }
        else if ("POINT_ng_edge_point_y" == strParamName || "POINT_ng_edge_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0; i<arrValue.size(); ++i) edgeNgY.push_back(arrValue[i].toDouble());
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    auto iMaxSize = calcMaxValue(edgeOkX,edgeOkY).size();
    for(int i=0; i<iMaxSize; ++i)
    {
        DiameterMeasureRunResult::EdgePoint pt;
        if (edgeOkX.size()>i) pt.x = edgeOkX[i];
        if (edgeOkY.size()>i) pt.x = edgeOkY[i];
        pRunResult->okPoints.append(pt);
    }
    iMaxSize = calcMaxValue(edgeNgX,edgeNgY).size();
    for(int i=0; i<iMaxSize; ++i)
    {
        DiameterMeasureRunResult::EdgePoint pt;
        if (edgeNgX.size()>i) pt.x = edgeNgX[i];
        if (edgeNgY.size()>i) pt.x = edgeNgY[i];
        pRunResult->ngPoints.append(pt);
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, WidthMeasureRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    WidthMeasureRunResult::MarkLines edgeLine;
    WidthMeasureRunResult::MarkLines edgeLine0;
    WidthMeasureRunResult::MarkLines edgeLine1;
    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_rst_measure" == strParamName || "SINGLE_rst_measure" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->width = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_l" == strParamName || "SINGLE_rst_measure_limit_l" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitDown = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_h" == strParamName || "SINGLE_rst_measure_limit_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitUp = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_x" == strParamName || "SINGLE_show_text_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->showTextX = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_y" == strParamName || "SINGLE_show_text_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->showTextY = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_ang" == strParamName || "SINGLE_show_text_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->showTextAng = arrValue[0].toDouble(0);
        }
        else if ("POINT_line_s_x" == strParamName || "POINT_line_s_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine.startX = arrValue[0].toDouble(0);
        }
        else if ("POINT_line_s_y" == strParamName || "POINT_line_s_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine.startY = arrValue[0].toDouble(0);
        }
        else if ("POINT_line_e_x" == strParamName || "POINT_line_e_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine.endX = arrValue[0].toDouble(0);
        }
        else if ("POINT_line_e_y" == strParamName || "POINT_line_e_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine.endY = arrValue[0].toDouble(0);
        }
        else if ("LINE1_edge0_s_point_x" == strParamName || "LINE1_edge0_s_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine0.startX = arrValue[0].toDouble(0);
        }
        else if ("LINE1_edge0_s_point_y" == strParamName || "LINE1_edge0_s_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine0.startY = arrValue[0].toDouble(0);
        }
        else if ("LINE1_edge0_e_point_x" == strParamName || "LINE1_edge0_e_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine0.endX = arrValue[0].toDouble(0);
        }
        else if ("LINE1_edge0_e_point_y" == strParamName || "LINE1_edge0_e_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine0.endY = arrValue[0].toDouble(0);
        }
        else if ("LINE1_edge0_angle" == strParamName || "LINE1_edge0_angle" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine0.angle = arrValue[0].toDouble(0);
        }
        else if ("LINE2_edge1_s_point_x" == strParamName || "LINE2_edge1_s_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine1.startX = arrValue[0].toDouble(0);
        }
        else if ("LINE2_edge1_s_point_y" == strParamName || "LINE2_edge1_s_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine1.startY = arrValue[0].toDouble(0);
        }
        else if ("LINE2_edge1_e_point_x" == strParamName || "LINE2_edge1_e_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine1.endX = arrValue[0].toDouble(0);
        }
        else if ("LINE2_edge1_e_point_y" == strParamName || "LINE2_edge1_e_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine1.endY = arrValue[0].toDouble(0);
        }
        else if ("LINE2_edge1_angle" == strParamName || "LINE2_edge1_angle" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) edgeLine1.angle = arrValue[0].toDouble(0);
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    pRunResult->markLines.append(edgeLine);
    pRunResult->markLines.append(edgeLine0);
    pRunResult->markLines.append(edgeLine1);
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, IdeModuleRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    QVector<int> vcStatus;
    QVector<QString> vcText;
    QVector<double> vcScore;
    QVector<QString> vcType;

    QVector<double> vcCenterX;
    QVector<double> vcCenterY;
    QVector<double> vcWidth;
    QVector<double> vcHeight;
    QVector<double> vcAngle;

    QVector<double> vcXScore;
    QVector<double> vcYScore;
    QVector<double> vcAngScore;

    QVector<double> vcXText;
    QVector<double> vcYText;
    QVector<double> vcAngText;

    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_rst_num_limit_l" == strParamName || "SINGLE_rst_num_limit_l" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            if (arrValue.size()>0) pRunResult->codeLimitDown = arrValue[0].toInt(0);
        }
        else if ("SINGLE_rst_num_limit_h" == strParamName || "SINGLE_rst_num_limit_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            if (arrValue.size()>0) pRunResult->codeLimitUp = arrValue[0].toInt(0);
        }
        else if ("SINGLE_code_status" == strParamName || "SINGLE_code_status" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcStatus.append(arrValue[i].toInt());
        }
        else if ("SINGLE_code_string" == strParamName || "SINGLE_code_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcText.append(arrValue[i].toObject()["strValue"].toString());
        }
        else if ("SINGLE_code_score" == strParamName || "SINGLE_code_score" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_code_type" == strParamName || "SINGLE_code_type" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcType.append(arrValue[i].toObject()["strValue"].toString());
        }
        else if ("BOX_code_box_cx" == strParamName || "BOX_code_box_cx" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcCenterX.append(arrValue[i].toDouble());
        }
        else if ("BOX_code_box_cy" == strParamName || "BOX_code_box_cy" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcCenterY.append(arrValue[i].toDouble());
        }
        else if ("BOX_code_box_w" == strParamName || "BOX_code_box_w" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcWidth.append(arrValue[i].toDouble());
        }
        else if ("BOX_code_box_h" == strParamName || "BOX_code_box_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcHeight.append(arrValue[i].toDouble());
        }
        else if ("BOX_code_box_ang" == strParamName || "BOX_code_box_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngle.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_x" == strParamName || "SINGLE_show_text_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcXScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_y" == strParamName || "SINGLE_show_text_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcYScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_ang" == strParamName || "SINGLE_show_text_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_x" == strParamName || "SINGLE_show_string_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcXText.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_y" == strParamName || "SINGLE_show_string_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcYText.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_angle" == strParamName || "SINGLE_show_string_angle" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngText.append(arrValue[i].toDouble());
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }

    auto iMaxSize = calcMaxValue(vcStatus.size(),vcText.size(),vcScore.size(),vcType.size(),vcCenterX.size(),vcCenterY.size(),
                                 vcWidth.size(),vcHeight.size(),vcAngle.size(),vcXScore.size(),vcYScore.size(),vcAngScore.size(),
                                 vcXText.size(),vcYText.size(),vcAngText.size());

    for (int i=0; i<iMaxSize; ++i)
    {
        IdeModuleRunResult::CodeValues codeValue;
        if (vcStatus.size()>i) codeValue.status = vcStatus[i];
        if (vcText.size()>i) codeValue.content = vcText[i];
        if (vcScore.size()>i) codeValue.score = vcScore[i];
        if (vcType.size()>i) codeValue.type = vcType[i];

        if (vcCenterX.size()>i) codeValue.boxArea.centerX = vcCenterX[i];
        if (vcCenterY.size()>i) codeValue.boxArea.centerY = vcCenterY[i];
        if (vcWidth.size()>i) codeValue.boxArea.width = vcWidth[i];
        if (vcHeight.size()>i) codeValue.boxArea.height = vcHeight[i];
        if (vcAngle.size()>i) codeValue.boxArea.angle = vcAngle[i];

        if (vcXScore.size()>i) codeValue.scoreShowArea.x = vcXScore[i];
        if (vcYScore.size()>i) codeValue.scoreShowArea.y = vcYScore[i];
        if (vcAngScore.size()>i) codeValue.scoreShowArea.angle = vcAngScore[i];

        if (vcXText.size()>i) codeValue.contentShowArea.x = vcXText[i];
        if (vcYText.size()>i) codeValue.contentShowArea.y = vcYText[i];
        if (vcAngText.size()>i) codeValue.contentShowArea.angle = vcAngText[i];

        pRunResult->codeValues.push_back(codeValue);
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, DlocrDetectRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    QVector<int> vcStatus;
    QVector<QString> vcText;
    QVector<double> vcScore;

    QVector<double> vcCenterX;
    QVector<double> vcCenterY;
    QVector<double> vcWidth;
    QVector<double> vcHeight;
    QVector<double> vcAngle;

    QVector<double> vcXScore;
    QVector<double> vcYScore;
    QVector<double> vcAngScore;

    QVector<double> vcXText;
    QVector<double> vcYText;
    QVector<double> vcAngText;

    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_rst_num_limit_l" == strParamName || "SINGLE_rst_num_limit_l" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            if (arrValue.size()>0) pRunResult->charLimitDown = arrValue[0].toInt(0);
        }
        else if ("SINGLE_rst_num_limit_h" == strParamName || "SINGLE_rst_num_limit_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            if (arrValue.size()>0) pRunResult->charLimitUp = arrValue[0].toInt(0);
        }
        else if ("SINGLE_ocr_obj_status" == strParamName || "SINGLE_ocr_obj_status" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pIntValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcStatus.append(arrValue[i].toInt());
        }
        else if ("SINGLE_obj_char_info_1" == strParamName || "SINGLE_obj_char_info_1" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcText.append(arrValue[i].toObject()["strValue"].toString());
        }
        else if ("SINGLE_obj_char_confidence_1" == strParamName || "SINGLE_obj_char_confidence_1" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcScore.append(arrValue[i].toDouble());
        }
        else if ("BOX_det_box_cx" == strParamName || "BOX_det_box_cx" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcCenterX.append(arrValue[i].toDouble());
        }
        else if ("BOX_det_box_cy" == strParamName || "BOX_det_box_cy" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcCenterY.append(arrValue[i].toDouble());
        }
        else if ("BOX_det_box_w" == strParamName || "BOX_det_box_w" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcWidth.append(arrValue[i].toDouble());
        }
        else if ("BOX_det_box_h" == strParamName || "BOX_det_box_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcHeight.append(arrValue[i].toDouble());
        }
        else if ("BOX_det_box_ang" == strParamName || "BOX_det_box_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngle.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_x" == strParamName || "SINGLE_show_text_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcXScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_y" == strParamName || "SINGLE_show_text_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcYScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_text_ang" == strParamName || "SINGLE_show_text_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngScore.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_x" == strParamName || "SINGLE_show_string_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcXText.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_y" == strParamName || "SINGLE_show_string_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcYText.append(arrValue[i].toDouble());
        }
        else if ("SINGLE_show_string_angle" == strParamName || "SINGLE_show_string_angle" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcAngText.append(arrValue[i].toDouble());
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }

    auto iMaxSize = calcMaxValue(vcStatus.size(),vcText.size(),vcScore.size(),vcCenterX.size(),vcCenterY.size(),vcWidth.size(),
                                 vcHeight.size(),vcAngle.size(),vcXScore.size(),vcYScore.size(),vcAngScore.size(),
                                 vcXText.size(),vcYText.size(),vcAngText.size());

    for (int i=0; i<iMaxSize; ++i)
    {
        DlocrDetectRunResult::CharValues codeValue;
        if (vcStatus.size()>i) codeValue.status = vcStatus[i];
        if (vcText.size()>i) codeValue.content = vcText[i];
        if (vcScore.size()>i) codeValue.score = vcScore[i];

        if (vcCenterX.size()>i) codeValue.boxArea.centerX = vcCenterX[i];
        if (vcCenterY.size()>i) codeValue.boxArea.centerY = vcCenterY[i];
        if (vcWidth.size()>i) codeValue.boxArea.width = vcWidth[i];
        if (vcHeight.size()>i) codeValue.boxArea.height = vcHeight[i];
        if (vcAngle.size()>i) codeValue.boxArea.angle = vcAngle[i];

        if (vcXScore.size()>i) codeValue.scoreShowArea.x = vcXScore[i];
        if (vcYScore.size()>i) codeValue.scoreShowArea.y = vcYScore[i];
        if (vcAngScore.size()>i) codeValue.scoreShowArea.angle = vcAngScore[i];

        if (vcXText.size()>i) codeValue.contentShowArea.x = vcXText[i];
        if (vcYText.size()>i) codeValue.contentShowArea.y = vcYText[i];
        if (vcAngText.size()>i) codeValue.contentShowArea.angle = vcAngText[i];

        pRunResult->charValues.push_back(codeValue);
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, GreyAreaRunResult* pRunResult, const QImage& renderImage)
{
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    if (!renderImage.isNull())
    {
        pRunResult->frame = CDobotDevice::image2Base64Byte(renderImage);
    }
    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_rst_measure" == strParamName || "SINGLE_rst_measure" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->area = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_l" == strParamName || "SINGLE_rst_measure_limit_l" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitDown = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_rst_measure_limit_h" == strParamName || "SINGLE_rst_measure_limit_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->limitUp = arrValue[0].toDouble(0);
        }
        else if ("BOX_det_box_cx" == strParamName || "BOX_det_box_cx" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->boxArea.centerX = arrValue[0].toDouble(0);
        }
        else if ("BOX_det_box_cy" == strParamName || "BOX_det_box_cy" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->boxArea.centerY = arrValue[0].toDouble(0);
        }
        else if ("BOX_det_box_w" == strParamName || "BOX_det_box_w" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->boxArea.width = arrValue[0].toDouble(0);
        }
        else if ("BOX_det_box_h" == strParamName || "BOX_det_box_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->boxArea.height = arrValue[0].toDouble(0);
        }
        else if ("BOX_det_box_ang" == strParamName || "BOX_det_box_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->boxArea.angle = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_x" == strParamName || "SINGLE_show_text_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->areaShowArea.x = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_y" == strParamName || "SINGLE_show_text_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->areaShowArea.y = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_show_text_ang" == strParamName || "SINGLE_show_text_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->areaShowArea.angle = arrValue[0].toDouble(0);
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, MatchCalibRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;

    QVector<double> vcImgX;
    QVector<double> vcImgY;
    QVector<double> vcPhysicX;
    QVector<double> vcPhysicY;

    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_calib_trans_err" == strParamName || "SINGLE_calib_trans_err" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->transformDelta = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_calib_rotation_err" == strParamName || "SINGLE_calib_rotation_err" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->rotationDelta = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_match_score" == strParamName || "SINGLE_match_score" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->score = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_calib_count_rate" == strParamName || "SINGLE_calib_count_rate" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) pRunResult->progress = arrValue[0].toObject().value("strValue").toString();
        }
        else if ("BOX1_match_box_cx" == strParamName || "BOX1_match_box_cx" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.centerX = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_cy" == strParamName || "BOX1_match_box_cy" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.centerY = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_w" == strParamName || "BOX1_match_box_w" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.width = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_h" == strParamName || "BOX1_match_box_h" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.height = arrValue[0].toDouble(0);
        }
        else if ("BOX1_match_box_ang" == strParamName || "BOX1_match_box_ang" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchBox.angle = arrValue[0].toDouble(0);
        }
        else if ("POINT_match_point_x" == strParamName || "POINT_match_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchPoint.x = arrValue[0].toDouble(0);
        }
        else if ("POINT_match_point_y" == strParamName || "POINT_match_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->matchPoint.y = arrValue[0].toDouble(0);
        }
        else if ("POINT1_output_image_point_x" == strParamName || "POINT1_output_image_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcImgX.append(arrValue[i].toDouble());
        }
        else if ("POINT1_output_image_point_y" == strParamName || "POINT1_output_image_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcImgY.append(arrValue[i].toDouble());
        }
        else if ("POINT2_output_phy_point_x" == strParamName || "POINT2_output_phy_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcPhysicX.append(arrValue[i].toDouble());
        }
        else if ("POINT2_output_phy_point_y" == strParamName || "POINT2_output_phy_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            for (int i=0;i<arrValue.size();++i) vcPhysicY.append(arrValue[i].toDouble());
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }
    auto iMaxSize = calcMaxValue(vcImgX.size(),vcImgY.size(),vcPhysicX.size(),vcPhysicY.size());

    for (int i=0; i<iMaxSize; ++i)
    {
        MatchCalibRunResult::OutputPoint codeValue;
        if (vcImgX.size()>i) codeValue.imageX = vcImgX[i];
        if (vcImgY.size()>i) codeValue.imageY = vcImgY[i];
        if (vcPhysicX.size()>i) codeValue.physicalX = vcPhysicX[i];
        if (vcPhysicY.size()>i) codeValue.physicalY = vcPhysicY[i];

        pRunResult->outputPoints.push_back(codeValue);
    }
    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}

static QString parsePInfo(const QJsonArray& arrPInfo, MatchLocateRunResult* pRunResult, const QImage& renderImage)
{
    Q_UNUSED(renderImage)
    QString strResult = "";
    int SINGLE_status = 0;
    int SINGLE_param_status = 0;
    for (auto itr=arrPInfo.begin(); itr!=arrPInfo.end(); ++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject infoObj = itr->toObject();

        const int nValueStatus = infoObj.value("nValueStatus").toInt(0); //算法运行的状态（运行正常为1，否则为0）
        const QString strParamName = infoObj.value("strParamName").toString();
        const QString strResultTypeName = infoObj.value("strResultTypeName").toString();

        if ("SINGLE_pixel_scale" == strParamName || "SINGLE_pixel_scale" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->precision = arrValue[0].toDouble(0);
        }
        else if ("POINT2_world_point_x" == strParamName || "POINT2_world_point_x" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->physicalX = arrValue[0].toDouble(0);
        }
        else if ("POINT2_world_point_y" == strParamName || "POINT2_world_point_y" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->physicalY = arrValue[0].toDouble(0);
        }
        else if ("POINT3_world_point_x_diff" == strParamName || "POINT3_world_point_x_diff" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->offsetX = arrValue[0].toDouble(0);
        }
        else if ("POINT3_world_point_y_diff" == strParamName || "POINT3_world_point_y_diff" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->offsetY = arrValue[0].toDouble(0);
        }
        else if ("SINGLE_world_point_angle_diff" == strParamName || "SINGLE_world_point_angle_diff" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pFloatValue").toArray();
            if (arrValue.size()>0) pRunResult->offsetTheta = arrValue[0].toDouble(0);
        }
        //运行状态结果
        else if ("SINGLE_status" == strParamName || "SINGLE_status" == strResultTypeName)
        {
            SINGLE_status = nValueStatus;
        }
        else if ("SINGLE_param_status" == strParamName || "SINGLE_param_status" == strResultTypeName)
        {
            SINGLE_param_status = nValueStatus;
        }
        else if ("SINGLE_param_status_string" == strParamName || "SINGLE_param_status_string" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) strResult = arrValue[0].toObject().value("strValue").toString("NG");
        }
        //运行结果判断依据
        else if ("SINGLE_rst_string_cn" == strParamName || "SINGLE_rst_string_cn" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefCN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefCN = "";
        }
        else if ("SINGLE_rst_string_en" == strParamName || "SINGLE_rst_string_en" == strResultTypeName)
        {
            QJsonArray arrValue = infoObj.value("pStringValue").toArray();
            if (arrValue.size()>0) g_RunResultTempData.strResultRefEN = arrValue[0].toObject().value("strValue").toString();
            else g_RunResultTempData.strResultRefEN = "";
        }
    }

    if (strResult.isEmpty())
    {
        if (1 == SINGLE_status && 1 == SINGLE_param_status) strResult = "OK";
        else strResult = "NG";
    }
    return strResult;
}
