QT += gui network

TEMPLATE = lib
CONFIG += c++11

TARGET = HKIndustrialCameraPlugin

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
    DataBean/BeginCalibrateBean.cpp \
    DataBean/CalcGetCalibrateResult.cpp \
    DataBean/CalibrateSampling.cpp \
    DataBean/CameraParamBean.cpp \
    DataBean/CloseCameraBean.cpp \
    DataBean/CreateUserCoordinate.cpp \
    DataBean/CreateUserCoordinateV2.cpp \
    DataBean/EndCalibrateBean.cpp \
    DataBean/GenerateCalibrateFile.cpp \
    DataBean/GenerateCalibrateFileV2.cpp \
    DataBean/GetCalibratePos.cpp \
    DataBean/OpenCameraBean.cpp \
    DataBean/SearchCameraBean.cpp \
    DataBean/SetIpConfigBean.cpp \
    DataBean/StartVideoBean.cpp \
    DataBean/StopVideoBean.cpp \
    DataBean/TakePhotoBean.cpp \
    DobotDevice.cpp \
    DobotDeviceFuncMapper.cpp \
    HKIndustrialCameraDevice.cpp \
    HKIndustrialCameraPlugin.cpp \
    ICameraDevice.cpp

HEADERS += \
    CameraInfo.h \
    DataBean/BeginCalibrateBean.h \
    DataBean/CalcGetCalibrateResult.h \
    DataBean/CalibrateSampling.h \
    DataBean/CameraParamBean.h \
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
    HKIndustrialCameraDevice.h \
    HKIndustrialCameraPlugin.h \
    ICameraDevice.h \
    IndustrialCameraStruct.h


###############################################################
include("../Common/Common.pri")

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
