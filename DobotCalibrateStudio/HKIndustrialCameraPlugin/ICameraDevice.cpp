#include "ICameraDevice.h"

ICameraDevice::ICameraDevice(QObject *parent) : QObject(parent)
{
    m_iErrCode = 0;
}

ICameraDevice::~ICameraDevice()
{
}
