
CONFIG += c++11

HEADERS += \
    $$PWD/MessageCenter/MessageCenter.h \
    $$PWD/MessageCenter/MessageCenterPrivate.h \
    $$PWD/PluginManager/PluginManager.h \
    $$PWD/ServerManager/IServerInterface.h \
    $$PWD/ServerManager/TcpServer.h \
    $$PWD/ServerManager/UdpBroadcastSelfIP.h \
    $$PWD/ServerManager/WebsocketServer.h

SOURCES += \
    $$PWD/MessageCenter/MessageCenter.cpp \
    $$PWD/PluginManager/PluginManager.cpp \
    $$PWD/ServerManager/TcpServer.cpp \
    $$PWD/ServerManager/UdpBroadcastSelfIP.cpp \
    $$PWD/ServerManager/WebsocketServer.cpp







