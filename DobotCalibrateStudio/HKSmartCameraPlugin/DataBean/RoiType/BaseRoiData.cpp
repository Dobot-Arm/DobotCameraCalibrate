#include "BaseRoiData.h"
#include "BoxRoiData.h"
#include "CircleRoiData.h"
#include "PolygonRoiData.h"
#include "AnnularRoiData.h"
#include "UnknowRoiData.h"

std::shared_ptr<BaseRoiData> BaseRoiData::createBase(QString strType)
{
    std::shared_ptr<BaseRoiData> sptr;
    if (BoxRoiData::isMine(strType)) sptr.reset(new BoxRoiData);
    else if (CircleRoiData::isMine(strType)) sptr.reset(new CircleRoiData);
    else if (PolygonRoiData::isMine(strType)) sptr.reset(new PolygonRoiData);
    else if (AnnularRoiData::isMine(strType)) sptr.reset(new AnnularRoiData);
    else sptr.reset(new UnknowRoiData);
    return sptr;
}
