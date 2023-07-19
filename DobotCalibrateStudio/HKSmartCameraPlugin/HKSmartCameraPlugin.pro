QT += gui network xml

TEMPLATE = lib
CONFIG += c++11

TARGET = HKSmartCameraPlugin

contains(QT_ARCH, i386) {
    TARGET_OUTPUT_DIR=x86_output
} else {
    TARGET_OUTPUT_DIR=x64_output
}
CONFIG(release, debug|release): DESTDIR = $$PWD/../../$${TARGET_OUTPUT_DIR}/Release
else:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../$${TARGET_OUTPUT_DIR}/Debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraInfo.cpp \
    DataBean/Add25DCalibrateFileBean.cpp \
    DataBean/Add25DCalibrateFileV2Bean.cpp \
    DataBean/Add2DCalibrateFileBean.cpp \
    DataBean/Add2DCalibrateFileV2Bean.cpp \
    DataBean/AddModuleBean.cpp \
    DataBean/AllSupportModuleBean.cpp \
    DataBean/BaseImageHistoryImageInfoListBean.cpp \
    DataBean/BaseImageHistroyImageDataBean.cpp \
    DataBean/BeginCalibrateBean.cpp \
    DataBean/CalcGetCalibrateResult.cpp \
    DataBean/CalibrateSampling.cpp \
    DataBean/CameraSoftRebootBean.cpp \
    DataBean/CloseCameraBean.cpp \
    DataBean/CopyModuleBean.cpp \
    DataBean/CopyProjectBean.cpp \
    DataBean/CreateProjectBean.cpp \
    DataBean/CreateUserCoordinate.cpp \
    DataBean/CreateUserCoordinateV2.cpp \
    DataBean/CurrentProgressBean.cpp \
    DataBean/CurrentSelectedProjectBean.cpp \
    DataBean/Delete25DCalibrateFileBean.cpp \
    DataBean/Delete2DCalibrateFileBean.cpp \
    DataBean/DeleteModuleBean.cpp \
    DataBean/DeleteProjectBean.cpp \
    DataBean/EndCalibrateBean.cpp \
    DataBean/Export2DCalibrateParamBean.cpp \
    DataBean/Export2DCalibrateParamV2Bean.cpp \
    DataBean/ExportProjectBean.cpp \
    DataBean/GenerateCalibrateFile.cpp \
    DataBean/GenerateCalibrateFileV2.cpp \
    DataBean/Get25DCalibrateFileListBean.cpp \
    DataBean/Get2DCalibrateFileListBean.cpp \
    DataBean/Get2DInputPointSupportListBean.cpp \
    DataBean/Get2DInputPointValueBean.cpp \
    DataBean/GetCalibratePos.cpp \
    DataBean/GetCameraCalibratePointBean.cpp \
    DataBean/GetCommunicateEnableBean.cpp \
    DataBean/GetCurrentProjectRunningStateBean.cpp \
    DataBean/GetModuleShowNameBean.cpp \
    DataBean/GetModuleUIAllParameterBean.cpp \
    DataBean/GetOneKeyAdjustRunStateBean.cpp \
    DataBean/GetOutputCfgPrjResultCategoryBean.cpp \
    DataBean/GetOutputCfgPrjResultCustomLogicData.cpp \
    DataBean/GetOutputCfgPrjResultCustomLogicSupportList.cpp \
    DataBean/GetOutputResultDataListBean.cpp \
    DataBean/GetOutputResultSupportListBean.cpp \
    DataBean/GetProjectRunResultBean.cpp \
    DataBean/GetRoiContourPointsBean.cpp \
    DataBean/GetRoiModuleBean.cpp \
    DataBean/GetRoiTemplateBean.cpp \
    DataBean/GetSupportRoiInfoBean.cpp \
    DataBean/GetTemplateRoiMatchPointBean.cpp \
    DataBean/ImportProjectBean.cpp \
    DataBean/OpenCameraBean.cpp \
    DataBean/AllProjectListBean.cpp \
    DataBean/ProjectModuleBean.cpp \
    DataBean/ProjectShowImageBean.cpp \
    DataBean/RenameProjectBean.cpp \
    DataBean/ResetProjectRunResultBean.cpp \
    DataBean/ResetTemplateRoiMatchPointBean.cpp \
    DataBean/RoiType/AnnularRoiData.cpp \
    DataBean/RoiType/CircleRoiData.cpp \
    DataBean/RoiType/UnknowRoiData.cpp \
    DataBean/RunResult/BaseRunResult.cpp \
    DataBean/RunResult/DiameterMeasureRunResult.cpp \
    DataBean/RunResult/DlocrDetectRunResult.cpp \
    DataBean/RunResult/GreyAreaRunResult.cpp \
    DataBean/RunResult/IdeModuleRunResult.cpp \
    DataBean/RunResult/ImageExistRunResult.cpp \
    DataBean/RunResult/MacapriltagRunResult.cpp \
    DataBean/RunResult/MatchCalibRunResult.cpp \
    DataBean/RunResult/MatchLocateRunResult.cpp \
    DataBean/RunResult/WidthMeasureRunResult.cpp \
    DataBean/SaveAsProjectBean.cpp \
    DataBean/SaveProjectBean.cpp \
    DataBean/SearchCameraBean.cpp \
    DataBean/Set2DInputPointValueBean.cpp \
    DataBean/SetBaseImageFromCurrentBean.cpp \
    DataBean/SetBaseImageFromHistoryBean.cpp \
    DataBean/SetCameraCalibratePointBean.cpp \
    DataBean/SetCameraPwdBean.cpp \
    DataBean/SetCommunicateEnableBean.cpp \
    DataBean/SetIpConfigBean.cpp \
    DataBean/SetModuleShowNameBean.cpp \
    DataBean/SetModuleUIParameterBean.cpp \
    DataBean/SetOutputCfgPrjResultCustomLogicData.cpp \
    DataBean/SetOutputResultDataListBean.cpp \
    DataBean/SetRoiModuleBean.cpp \
    DataBean/SetRoiTemplateBean.cpp \
    DataBean/SetTemplateRoiMatchPointBean.cpp \
    DataBean/StartTestVideoBean.cpp \
    DataBean/StartVideoBean.cpp \
    DataBean/StartVideoV2Bean.cpp \
    DataBean/StopVideoBean.cpp \
    DataBean/Switch2DCalibrateFileBean.cpp \
    DataBean/SwitchProjectBean.cpp \
    DataBean/Switch25DCalibrateFileBean.cpp \
    DataBean/TakeBasePhotoBean.cpp \
    DataBean/TakePhotoBean.cpp \
    DataBean/UIParamType/UIParamBase.cpp \
    DataBean/UIParamType/UIParamBoolean.cpp \
    DataBean/UIParamType/UIParamCommand.cpp \
    DataBean/UIParamType/UIParamEnumeration.cpp \
    DataBean/UIParamType/UIParamFloat.cpp \
    DataBean/UIParamType/UIParamInteger.cpp \
    DataBean/UIParamType/UIParamString.cpp \
    DataBean/UIParamType/UIParamUnknow.cpp \
    DobotDevice.cpp \
    DobotDeviceFunc.cpp \
    DobotDeviceFuncMapper.cpp \
    HKSmartCameraDevice.cpp \
    HKSmartCameraPlugin.cpp \
    DataBean/RoiType/BaseRoiData.cpp \
    DataBean/RoiType/BoxRoiData.cpp \
    DataBean/RoiType/PolygonRoiData.cpp

HEADERS += \
    CameraInfo.h \
    DataBean/Add25DCalibrateFileBean.h \
    DataBean/Add25DCalibrateFileV2Bean.h \
    DataBean/Add2DCalibrateFileBean.h \
    DataBean/Add2DCalibrateFileV2Bean.h \
    DataBean/AddModuleBean.h \
    DataBean/AllSupportModuleBean.h \
    DataBean/BaseImageHistoryImageInfoListBean.h \
    DataBean/BaseImageHistroyImageDataBean.h \
    DataBean/CameraSoftRebootBean.h \
    DataBean/CopyModuleBean.h \
    DataBean/CopyProjectBean.h \
    DataBean/CreateProjectBean.h \
    DataBean/CurrentProgressBean.h \
    DataBean/CurrentSelectedProjectBean.h \
    DataBean/Delete25DCalibrateFileBean.h \
    DataBean/Delete2DCalibrateFileBean.h \
    DataBean/DeleteModuleBean.h \
    DataBean/DeleteProjectBean.h \
    DataBean/Export2DCalibrateParamBean.h \
    DataBean/Export2DCalibrateParamV2Bean.h \
    DataBean/ExportProjectBean.h \
    DataBean/Get25DCalibrateFileListBean.h \
    DataBean/Get2DCalibrateFileListBean.h \
    DataBean/Get2DInputPointSupportListBean.h \
    DataBean/Get2DInputPointValueBean.h \
    DataBean/GetCameraCalibratePointBean.h \
    DataBean/GetCommunicateEnableBean.h \
    DataBean/GetCurrentProjectRunningStateBean.h \
    DataBean/GetModuleShowNameBean.h \
    DataBean/GetModuleUIAllParameterBean.h \
    DataBean/GetOneKeyAdjustRunStateBean.h \
    DataBean/GetOutputCfgPrjResultCategoryBean.h \
    DataBean/GetOutputCfgPrjResultCustomLogicData.h \
    DataBean/GetOutputCfgPrjResultCustomLogicSupportList.h \
    DataBean/GetOutputResultDataListBean.h \
    DataBean/GetOutputResultSupportListBean.h \
    DataBean/GetProjectRunResultBean.h \
    DataBean/GetRoiContourPointsBean.h \
    DataBean/GetRoiModuleBean.h \
    DataBean/GetRoiTemplateBean.h \
    DataBean/GetSupportRoiInfoBean.h \
    DataBean/GetTemplateRoiMatchPointBean.h \
    DataBean/ImportProjectBean.h \
    DataBean/AllProjectListBean.h \
    DataBean/ProjectModuleBean.h \
    DataBean/ProjectShowImageBean.h \
    DataBean/RenameProjectBean.h \
    DataBean/ResetProjectRunResultBean.h \
    DataBean/ResetTemplateRoiMatchPointBean.h \
    DataBean/RoiType/AnnularRoiData.h \
    DataBean/RoiType/CircleRoiData.h \
    DataBean/RoiType/UnknowRoiData.h \
    DataBean/RunResult/BaseRunResult.h \
    DataBean/RunResult/DiameterMeasureRunResult.h \
    DataBean/RunResult/DlocrDetectRunResult.h \
    DataBean/RunResult/GreyAreaRunResult.h \
    DataBean/RunResult/IdeModuleRunResult.h \
    DataBean/RunResult/ImageExistRunResult.h \
    DataBean/RunResult/MacapriltagRunResult.h \
    DataBean/RunResult/MatchCalibRunResult.h \
    DataBean/RunResult/MatchLocateRunResult.h \
    DataBean/RunResult/WidthMeasureRunResult.h \
    DataBean/SaveAsProjectBean.h \
    DataBean/SaveProjectBean.h \
    DataBean/Set2DInputPointValueBean.h \
    DataBean/SetBaseImageFromCurrentBean.h \
    DataBean/SetBaseImageFromHistoryBean.h \
    DataBean/SetCameraCalibratePointBean.h \
    DataBean/SetCameraPwdBean.h \
    DataBean/SetCommunicateEnableBean.h \
    DataBean/SetModuleShowNameBean.h \
    DataBean/SetModuleUIParameterBean.h \
    DataBean/SetOutputCfgPrjResultCustomLogicData.h \
    DataBean/SetOutputResultDataListBean.h \
    DataBean/SetRoiModuleBean.h \
    DataBean/SetRoiTemplateBean.h \
    DataBean/SetTemplateRoiMatchPointBean.h \
    DataBean/StartTestVideoBean.h \
    DataBean/StartVideoV2Bean.h \
    DataBean/Switch2DCalibrateFileBean.h \
    DataBean/SwitchProjectBean.h \
    DataBean/Switch25DCalibrateFileBean.h \
    DataBean/TakeBasePhotoBean.h \
    DataBean/UIParamType/UIParamBase.h \
    DataBean/UIParamType/UIParamBoolean.h \
    DataBean/UIParamType/UIParamCommand.h \
    DataBean/UIParamType/UIParamEnumeration.h \
    DataBean/UIParamType/UIParamFloat.h \
    DataBean/UIParamType/UIParamInteger.h \
    DataBean/UIParamType/UIParamString.h \
    DataBean/UIParamType/UIParamUnknow.h \
    DataBeanHeaderConfig.h \
    DataBean/RoiType/BaseRoiData.h \
    DataBean/RoiType/BoxRoiData.h \
    DataBean/RoiType/PolygonRoiData.h \
    SmartCameraStruct.h \
    DataBean/BeginCalibrateBean.h \
    DataBean/CalcGetCalibrateResult.h \
    DataBean/CalibrateSampling.h \
    DataBean/CloseCameraBean.h \
    DataBean/CreateUserCoordinate.h \
    DataBean/CreateUserCoordinateV2.h \
    DataBean/EndCalibrateBean.h \
    DataBean/GenerateCalibrateFile.h \
    DataBean/GenerateCalibrateFileV2.h \
    DataBean/GetCalibratePos.h \
    DataBean/OpenCameraBean.h \
    DataBean/SearchCameraBean.h \
    DataBean/SetIpConfigBean.h \
    DataBean/StartVideoBean.h \
    DataBean/StopVideoBean.h \
    DataBean/TakePhotoBean.h \
    DobotDevice.h \
    HKSmartCameraDevice.h \
    HKSmartCameraPlugin.h


###############################################################
include("../Common/Common.pri")
include("../yamlcpp/yamlcpp.pri")

INCLUDEPATH += \
    $$PWD/../Common \
    $$PWD/../DobotInterfacePlugin

LIBS += -L$$DESTDIR/ -lDobotInterfacePlugin

win32{
    LIBS += -lws2_32 -liphlpapi
}
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

linux {
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\':\'\$$ORIGIN/lib\',--enable-new-dtags"
}
