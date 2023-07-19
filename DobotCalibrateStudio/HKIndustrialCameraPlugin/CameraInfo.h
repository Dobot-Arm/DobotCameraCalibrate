#ifndef CAMERAINFO_H
#define CAMERAINFO_H

#include <QString>

class CameraInfo
{
public:
    CameraInfo();

    QString strIdentify;
    QString strIpAddress;
    QString strMacAddress;
    QString strSubNetMask;
    QString strGateWay;
    QString strSerialNumber;
    QString strManufacturerName; //厂商
    QString strVersion;
    QString strModelName;
    bool bDeviceAccessible; //相机是否可达，可连接，通常是被别人连接了或者ip地址不对导致false
    QString strNetExportAddress; //网口的ip地址，也就是网卡此时的ip
};

struct MyPointF3D
{
    double x;
    double y;
    double z;
};

struct MyPointF6D
{
    double x;
    double y;
    double z;
    double rx;
    double ry;
    double rz;
};

struct MyCameraIpInfo
{
    QString strIpAddress;
    QString strSubNetMask;
    QString strGateWay;
};

#endif // CAMERAINFO_H
