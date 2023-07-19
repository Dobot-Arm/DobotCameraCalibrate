QT -= gui

TEMPLATE = lib
CONFIG += c++11

TARGET = HKIndustrialIOControllerPlugin

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
    DataBean/IODeviceClose.cpp \
    DataBean/IODeviceGetLightParam.cpp \
    DataBean/IODeviceLightTurnOff.cpp \
    DataBean/IODeviceLightTurnOn.cpp \
    DataBean/IODeviceOpen.cpp \
    DobotDevice.cpp \
    DobotDeviceFuncMapper.cpp \
    HKIndustrialIOControllerPlugin.cpp \
    HKIndustrialIODevice.cpp

HEADERS += \
    DataBean/IODeviceClose.h \
    DataBean/IODeviceGetLightParam.h \
    DataBean/IODeviceLightTurnOff.h \
    DataBean/IODeviceLightTurnOn.h \
    DataBean/IODeviceOpen.h \
    DobotDevice.h \
    HKIndustrialIOControllerPlugin.h \
    HKIndustrialIODevice.h


###############################################################
include("../Common/Common.pri")

INCLUDEPATH += \
    $$PWD/../Common \
    $$PWD/../DobotInterfacePlugin

LIBS += -L$$DESTDIR/ -lDobotInterfacePlugin

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

linux {
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\':\'\$$ORIGIN/lib\',--enable-new-dtags"
}
