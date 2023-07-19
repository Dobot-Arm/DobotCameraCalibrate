#include "DobotDevice.h"
#include "JsonMessage.h"

void CDobotDevice::initFunctionMapper()
{
#define FUNC_MAPPER(api) if(!m_mapperFunction.contains(#api)) m_mapperFunction.insert(#api, &CDobotDevice::api)

    FUNC_MAPPER(search);
    FUNC_MAPPER(setIpConfig);
    FUNC_MAPPER(open);
    FUNC_MAPPER(close);
    FUNC_MAPPER(startVideo);
    FUNC_MAPPER(stopVideo);
    FUNC_MAPPER(takePhoto);
    FUNC_MAPPER(getCalibratePos);
    FUNC_MAPPER(calcGetCalibrateResult);
    FUNC_MAPPER(generateCalibrateFile);
    FUNC_MAPPER(generateCalibrateFileV2);
    FUNC_MAPPER(createUserCoordinate);
    FUNC_MAPPER(createUserCoordinateV2);
    FUNC_MAPPER(beginCalibrate);
    FUNC_MAPPER(endCalibrate);
    FUNC_MAPPER(calibrateSampling);
    FUNC_MAPPER(updateCalibrateSampling);
    FUNC_MAPPER(getCameraParam);
    FUNC_MAPPER(setCameraParam);
}
