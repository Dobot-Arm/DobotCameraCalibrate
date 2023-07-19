QT -= gui

TEMPLATE = lib
CONFIG += c++11

TARGET = DobotInterfacePlugin

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

DEFINES += DOBOT_INTERFACEPLUGIN_CLASS_LIBRARY

SOURCES += \
    DobotInterfacePlugin.cpp

HEADERS += \
    DobotInterfacePlugin.h \
    DobotInterfacePluginPrivate.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

linux {
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\':\'\$$ORIGIN/lib\',--enable-new-dtags"
}
