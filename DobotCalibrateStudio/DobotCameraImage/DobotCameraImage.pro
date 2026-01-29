QT += core websockets network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = DobotCameraImage

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
    DataBean/CloseCameraBean.cpp \
    DataBean/OpenCameraBean.cpp \
    DataBean/SearchCameraBean.cpp \
    DataBean/StartVideoImageBean.cpp \
    DataBean/StopVideoBean.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DataBean/CloseCameraBean.h \
    DataBean/OpenCameraBean.h \
    DataBean/SearchCameraBean.h \
    DataBean/StartVideoImageBean.h \
    DataBean/StopVideoBean.h \
    MainWindow.h


###############################################################
include("../Common/Common.pri")
include("../DobotServer/DobotServer.pri")

INCLUDEPATH += \
    $$PWD/../Common \
    $$PWD/../DobotServer \
    $$PWD/../DobotInterfacePlugin

LIBS += -L$$DESTDIR/ -lDobotInterfacePlugin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

linux {
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\':\'\$$ORIGIN/lib\',--enable-new-dtags"
}

FORMS += \
    MainWindow.ui
