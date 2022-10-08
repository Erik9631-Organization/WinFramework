//
// Created by Erik on 08/10/22.
//

#ifndef LII_PRESENTATIONSUBJECT_H
#define LII_PRESENTATIONSUBJECT_H
#include "RenderingProvider.h"
#include "EventRenderingProviderInfo.h"
#include "EventAttributeInfo.h"
#include "EventResizeInfo.h"
#include "EventCursorLockInfo.h"

class PresentationSubject
{
    virtual void NotifyOnRenderingProviderChanged(EventRenderingProviderInfo& e) = 0;
    virtual void NotifyOnAttributesChanged(EventAttributeInfo& e) = 0;
    virtual void NotifyOnAttributesRemoved(EventAttributeInfo& e) = 0;
    virtual void NotifyOnScaleUpdate(std::any src) = 0;
    virtual void NotifyOnRedraw(std::any src) = 0;
    virtual void NotifyOnClose(std::any src) = 0;
    virtual void NotifyOnLockCursorSizeChanged(EventResizeInfo& e) = 0;
    virtual void NotifyOnCursorLockStateChanged(EventCursorLockInfo& e) = 0;
    virtual EventCursorLockInfo RequestCursorLockState(std::any src) = 0;
    virtual EventRenderingProviderInfo RequestRenderingProvider(std::any src) = 0;
};


#endif //LII_PRESENTATIONSUBJECT_H
