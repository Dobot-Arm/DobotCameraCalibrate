#ifndef SFTPCONNECTPARAM_H
#define SFTPCONNECTPARAM_H

#include<QString>
#include <QMetaType>

struct SFtpConnectParam
{
    QString strHost;
    quint16 iPort;
    QString strUserName;
    QString strPwd;
    int iTimeoutSeconds;
};
Q_DECLARE_METATYPE(SFtpConnectParam)

/*
SFtpConnectParam prm;
prm.iPort = 22;
prm.strPwd = "dobot";
prm.strHost = "192.168.5.1";
prm.strUserName = "root";
client->connectHost(prm);
*/

#endif // SFTPCONNECTPARAM_H
