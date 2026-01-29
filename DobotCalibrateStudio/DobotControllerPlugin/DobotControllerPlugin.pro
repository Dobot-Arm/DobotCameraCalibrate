QT -= gui
QT += core network

TEMPLATE = lib
CONFIG += c++11

TARGET = DobotControllerPlugin

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


HEADERS += \
    DataBean/DownloadFileBean.h \
    DataBean/GetAllProjectBean.h \
    DataBean/GetInfoListBean.h \
    DataBean/GetProjectFilesBean.h \
    DataBean/UploadFileBean.h \
    DataBean/ReadProjectFileBean.h \
    DataBean/WriteProjectFileBean.h \
    DataBeanHeaderConfig.h \
    DobotControllerPlugin.h \
    DobotDevice.h

SOURCES += \
    DataBean/DownloadFileBean.cpp \
    DataBean/GetAllProjectBean.cpp \
    DataBean/GetInfoListBean.cpp \
    DataBean/GetProjectFilesBean.cpp \
    DataBean/UploadFileBean.cpp \
    DataBean/ReadProjectFileBean.cpp \
    DataBean/WriteProjectFileBean.cpp \
    DobotControllerPlugin.cpp \
    DobotDevice.cpp \
    DobotDeviceFuncMapper.cpp


###############################################################
include("../Common/Common.pri")
include("../qssh/qssh.pri")

INCLUDEPATH += \
    $$PWD/../qssh \
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
