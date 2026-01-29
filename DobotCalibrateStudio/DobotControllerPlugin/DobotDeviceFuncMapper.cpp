#include "DobotDevice.h"
#include "JsonMessage.h"

void CDobotDevice::initFunctionMapper()
{
#define FUNC_MAPPER(api) if(!m_mapperFunction.contains(#api)) m_mapperFunction.insert(#api, &CDobotDevice::api)

    FUNC_MAPPER(getInfoList);
    FUNC_MAPPER(downloadFile);
    FUNC_MAPPER(uploadFile);
    FUNC_MAPPER(getAllProject);
    FUNC_MAPPER(getProjectFiles);
    FUNC_MAPPER(readProjectFile);
    FUNC_MAPPER(writeProjectFile);
}
