#include "UdpBroadcastSelfIP.h"
#include "DefineMicro.h"

#include <QUdpSocket>
#include <QNetworkProxy>
#include <QTimer>
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QJsonObject>

CUdpBroadcastSelfIP::CUdpBroadcastSelfIP(QObject *parent) : IServerInterface(parent)
{
    m_pUdpSocket = new QUdpSocket(this);
    m_pUdpSocket->setProxy(QNetworkProxy::NoProxy);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    connect(m_pTimer, &QTimer::timeout, this, &CUdpBroadcastSelfIP::slotBroadcastIp);
}

CUdpBroadcastSelfIP::~CUdpBroadcastSelfIP()
{
    m_pTimer->deleteLater();
    m_pUdpSocket->deleteLater();
}

bool CUdpBroadcastSelfIP::listen()
{
    m_pTimer->start();
    return true;
}

void CUdpBroadcastSelfIP::close()
{
    m_pTimer->stop();
}

void CUdpBroadcastSelfIP::sendMsgToClient(const CMessageResponse &)
{
}

void CUdpBroadcastSelfIP::slotBroadcastIp()
{
    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        QString strName = netInterface.humanReadableName();
        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if (!netInterface.isValid() ||
                !flags.testFlag(QNetworkInterface::IsUp) ||
                !flags.testFlag(QNetworkInterface::IsRunning))
        {
            continue;
        }

        QList<QNetworkAddressEntry> entryList = netInterface.addressEntries();
        //遍历每一个IP地址(每个包含一个IP地址，一个子网掩码和一个广播地址)
        foreach(QNetworkAddressEntry entry, entryList)
        {
            if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol ||
                    entry.ip().isLoopback() || entry.ip().isLinkLocal())
            {
                continue;
            }
            QString strMyIp = entry.ip().toString();
            if (!strMyIp.contains("192.168."))
            {
                continue;
            }

            QJsonObject json;
            json.insert("ip", strMyIp);
            json.insert("identify", "dobotCalibrate");
            QJsonDocument doc(json);
            QByteArray sendData = doc.toJson();
            sendData.append('\0');
            m_pUdpSocket->writeDatagram(sendData,entry.broadcast(),UDP_BROADCAST_SELF_IP);
        }
    }
}
