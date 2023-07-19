#include "UIParamBase.h"
#include "UIParamBoolean.h"
#include "UIParamCommand.h"
#include "UIParamEnumeration.h"
#include "UIParamFloat.h"
#include "UIParamInteger.h"
#include "UIParamString.h"
#include "UIParamUnknow.h"

std::shared_ptr<UIParamBase> UIParamBase::createBase(QString strType)
{
    std::shared_ptr<UIParamBase> sptr;
    if (UIParamBoolean::isMine(strType)) sptr.reset(new UIParamBoolean);
    else if (UIParamInteger::isMine(strType)) sptr.reset(new UIParamInteger);
    else if (UIParamFloat::isMine(strType)) sptr.reset(new UIParamFloat);
    else if (UIParamEnumeration::isMine(strType)) sptr.reset(new UIParamEnumeration);
    else if (UIParamString::isMine(strType)) sptr.reset(new UIParamString);
    else if (UIParamCommand::isMine(strType)) sptr.reset(new UIParamCommand);
    else sptr.reset(new UIParamUnknow);
    return sptr;
}
