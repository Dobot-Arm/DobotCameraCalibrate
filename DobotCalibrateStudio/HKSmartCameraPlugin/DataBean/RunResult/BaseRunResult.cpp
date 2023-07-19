#include "BaseRunResult.h"
#include "MacapriltagRunResult.h"
#include "ImageExistRunResult.h"
#include "DiameterMeasureRunResult.h"
#include "WidthMeasureRunResult.h"
#include "IdeModuleRunResult.h"
#include "DlocrDetectRunResult.h"
#include "GreyAreaRunResult.h"
#include "MatchCalibRunResult.h"
#include "MatchLocateRunResult.h"

std::shared_ptr<BaseRunResult> BaseRunResult::createBase(QString strType)
{
    std::shared_ptr<BaseRunResult> sptr;
    if (MacapriltagRunResult::isMine(strType)) sptr.reset(new MacapriltagRunResult);
    else if (ImageExistRunResult::isMine(strType)) sptr.reset(new ImageExistRunResult);
    else if (DiameterMeasureRunResult::isMine(strType)) sptr.reset(new DiameterMeasureRunResult);
    else if (WidthMeasureRunResult::isMine(strType)) sptr.reset(new WidthMeasureRunResult);
    else if (IdeModuleRunResult::isMine(strType)) sptr.reset(new IdeModuleRunResult);
    else if (DlocrDetectRunResult::isMine(strType)) sptr.reset(new DlocrDetectRunResult);
    else if (GreyAreaRunResult::isMine(strType)) sptr.reset(new GreyAreaRunResult);
    else if (MatchCalibRunResult::isMine(strType)) sptr.reset(new MatchCalibRunResult);
    else if (MatchLocateRunResult::isMine(strType)) sptr.reset(new MatchLocateRunResult);

    return sptr;
}
