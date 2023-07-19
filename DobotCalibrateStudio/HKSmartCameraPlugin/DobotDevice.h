#ifndef CDOBOTDEVICE_H
#define CDOBOTDEVICE_H

#include <QObject>
#include <QHash>
#include <QJsonObject>
#include <QMutex>

#include "JsonMessage.h"
#include "HKSmartCameraDevice.h"
#include "DataBeanHeaderConfig.h"

class CDobotDevice : public QObject
{
    Q_OBJECT
public:
    explicit CDobotDevice(QObject *parent = nullptr);
    ~CDobotDevice();
    static QByteArray image2Base64Byte(const QImage& img, const char *format = "jpg", int quality = -1);

    void doCmd(const CMessageRequest &msg);

    void closeNotResponse();

signals:
    void doResponseMsg(QJsonObject obj, QPrivateSignal);

private:
    void initFunctionMapper();
    void emitResponseMsg(const CMessageResponse& msg);
    void sendResponseSuccess(const QString& strMsgUuid, const CJsonMessage& responseData, bool bAutoDeleteCacheId=true);
    void sendResponseError(const QString& strMsgUuid, const int iErrCode, const QString& strErrMsg="", bool bAutoDeleteCacheId=true);
    void sendResponseError(const QString& strMsgUuid, const CJsonMessage& responseData, const int iErrCode, const QString& strErrMsg="", bool bAutoDeleteCacheId=true);
    void deleteAllCacheId();
    void deleteCacheId(const QString& strMsgUuid);
    bool checkIpAddressValid(const QString& strIp);

    QString fixSavePath(const QString& strPath);
    QString getMyCachePath() const;
    QString getLastTempCalibrateFile() const;
    void updateLastTempCalibrateFile(const QString& strSrcFile) const;

    /*解析解决方案运行结果
     * strResultInfo-方案运行结果json数据
     * renderImage-方案运行结果掩模图(渲染图)数据<moduleId,image>
    */
    void parseProjectRunResult(const QString &strResultInfo, const QHash<int,QImage>& renderImage,CGetProjectRunResultResponseBean2 &result);

    /************************************************************************/
    void search(const CMessageRequest &msg);
    void setIpConfig(const CMessageRequest &msg);
    void open(const CMessageRequest &msg);
    void close(const CMessageRequest &msg);
    void startVideo(const CMessageRequest &msg);
    void startVideoV2(const CMessageRequest &msg);
    void startTestVideo(const CMessageRequest &msg);
    void stopVideo(const CMessageRequest &msg);
    void takePhoto(const CMessageRequest &msg);
    void takeBasePhoto(const CMessageRequest &msg);
    void getCalibratePos(const CMessageRequest &msg);
    void calcGetCalibrateResult(const CMessageRequest &msg);
    void generateCalibrateFile(const CMessageRequest &msg);
    void generateCalibrateFileV2(const CMessageRequest &msg);
    void createUserCoordinate(const CMessageRequest &msg);
    void createUserCoordinateV2(const CMessageRequest &msg);
    void beginCalibrate(const CMessageRequest &msg);
    void endCalibrate(const CMessageRequest &msg);
    void calibrateSampling(const CMessageRequest &msg);
    void updateCalibrateSampling(const CMessageRequest &msg);
    void getCurrentProgress(const CMessageRequest &msg);
    void getAllProjectList(const CMessageRequest &msg);
    void getProjectShowImage(const CMessageRequest &msg);
    void getCurrentSelectedProject(const CMessageRequest &msg);
    void importProject(const CMessageRequest &msg);
    void exportProject(const CMessageRequest &msg);
    void createProject(const CMessageRequest &msg);
    void deleteProject(const CMessageRequest &msg);
    void copyProject(const CMessageRequest &msg);
    void renameProject(const CMessageRequest &msg);
    void saveProject(const CMessageRequest &msg);
    void saveAsProject(const CMessageRequest &msg);
    void switchProject(const CMessageRequest &msg);
    void getAllSupportModuleList(const CMessageRequest &msg);
    void getProjectModuleList(const CMessageRequest &msg);
    void addModule(const CMessageRequest &msg);
    void deleteModule(const CMessageRequest &msg);
    void copyModule(const CMessageRequest &msg);
    void setModuleShowName(const CMessageRequest &msg);
    void getModuleShowName(const CMessageRequest &msg);
    void getModuleUIAllParameters(const CMessageRequest &msg);
    void setModuleUIParameters(const CMessageRequest &msg);
    void setCameraPassword(const CMessageRequest &msg);
    void cameraSoftReboot(const CMessageRequest &msg);
    void setCommunicateEnable(const CMessageRequest &msg);
    void getCommunicateEnable(const CMessageRequest &msg);
    void get25DCalibrateFileList(const CMessageRequest &msg);
    void get2DCalibrateFileList(const CMessageRequest &msg);
    void delete25DCalibrateFile(const CMessageRequest &msg);
    void delete2DCalibrateFile(const CMessageRequest &msg);
    void switch25DCalibrateFile(const CMessageRequest &msg);
    void switch2DCalibrateFile(const CMessageRequest &msg);
    void add25DCalibrateFile(const CMessageRequest &msg);
    void add25DCalibrateFileV2(const CMessageRequest &msg);
    void add2DCalibrateFile(const CMessageRequest &msg);
    void add2DCalibrateFileV2(const CMessageRequest &msg);
    void export2DCalibrateParam(const CMessageRequest &msg);
    void export2DCalibrateParamV2(const CMessageRequest &msg);
    void getBaseImageHistroyImageInfoList(const CMessageRequest &msg);
    void getBaseImageHistroyImageData(const CMessageRequest &msg);
    void setBaseImageFromCurrent(const CMessageRequest &msg);
    void setBaseImageFromHistory(const CMessageRequest &msg);
    void getCurrentProjectRunningState(const CMessageRequest &msg);
    void getOutputConfigProjectResultCategory(const CMessageRequest &msg);
    void getOutputConfigProjectResultCustomLogicData(const CMessageRequest &msg);
    void setOutputConfigProjectResultCustomLogicData(const CMessageRequest &msg);
    void getOutputConfigProjectResultCustomLogicSupportList(const CMessageRequest &msg);
    void get2DInputPointSupportList(const CMessageRequest &msg);
    void get2DInputPointValue(const CMessageRequest &msg);
    void set2DInputPointValue(const CMessageRequest &msg);
    void getOneKeyAdjustRunState(const CMessageRequest &msg);
    void getSupportRoiInfo(const CMessageRequest &msg);
    void getRoiModule(const CMessageRequest &msg);
    void getRoiTemplate(const CMessageRequest &msg);
    void setRoiModule(const CMessageRequest &msg);
    void setRoiTemplate(const CMessageRequest &msg);
    void getRoiContourPoints(const CMessageRequest &msg);
    void setTemplateRoiMatchPoint(const CMessageRequest &msg);
    void getTemplateRoiMatchPoint(const CMessageRequest &msg);
    void resetTemplateRoiMatchPoint(const CMessageRequest &msg);
    void resetProjectRunResult(const CMessageRequest &msg);
    void getProjectRunResult(const CMessageRequest &msg);
    void getCameraCalibratePoint(const CMessageRequest &msg);
    void setCameraCalibratePoint(const CMessageRequest &msg);
    void getOutputResultSupportList(const CMessageRequest &msg);
    void getOutputResultDataList(const CMessageRequest &msg);
    void setOutputResultDataList(const CMessageRequest &msg);

private:
    typedef void (CDobotDevice::*pfnCmdCallback)(const CMessageRequest &msg);
    QHash<QString,      //method name
        pfnCmdCallback  //callback
    > m_mapperFunction;

    //msg request cache
    QHash<QString, //msg uuid
        RequestJsonRpc
    > m_requestCacheId;
    QMutex m_mtxRequestCacheId;

    /*拍视频时，因为msguuid并没有删除，否则下一次无法主动推送给别人，所以当停止时，则需要删掉缓存，否则遗留了。*/
    QString m_strVideoLastMsgUuid;

    HKSmartCameraDevice* m_pCameraDevice;

    //模块属性类型容器
    QMap<QString, //属性参数名
        MyVsXmlAttribute
    > m_mapAttributeType;

    //模块显示的文本
    QMap<QString, //模块名称moduleName
        MyModuleTranslate
    > m_mapTranslateString;

    //解决方案运行保存的临时结果
    CGetProjectRunResultResponseBean2 m_objProjectRunResult;
    QMutex m_mtxProjectRunResult;
};

#endif // CDOBOTDEVICE_H
