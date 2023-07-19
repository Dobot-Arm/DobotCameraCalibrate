#include "DobotDevice.h"
#include "JsonMessage.h"

void CDobotDevice::initFunctionMapper()
{
#define FUNC_MAPPER(api) if(!m_mapperFunction.contains(#api)) m_mapperFunction.insert(#api, &CDobotDevice::api)

    FUNC_MAPPER(open);
    FUNC_MAPPER(close);
    FUNC_MAPPER(lightTurnOn);
    FUNC_MAPPER(lightTurnOff);
    FUNC_MAPPER(getLightParam);
}
