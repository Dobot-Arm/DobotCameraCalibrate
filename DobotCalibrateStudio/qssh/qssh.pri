
CONFIG += c++11

HEADERS += \
    $$PWD/SFtpConnectParam.h \
    $$PWD/SFtpFileClient.h \
    $$PWD/ShellCmd.h

SOURCES += \
    $$PWD/SFtpFileClient.cpp \
    $$PWD/ShellCmd.cpp


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

contains(QT_ARCH, i386) {
    LIB_DIR_PRE=x86
} else {
    LIB_DIR_PRE=x64
}
CONFIG(release, debug|release): {
    LIBS += -L$$PWD/lib/$${LIB_DIR_PRE} -lQSsh
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/lib/$${LIB_DIR_PRE} -lQSshd
}
