//
// Created by Erik on 09/10/22.
//

#ifndef LII_PRESENTERSUBJECT_H
#define LII_PRESENTERSUBJECT_H
#include "EventAttributeInfo.h"
#include "EventRenderingProviderInfo.h"
#include "Renderer.h"
#include "EventResizeInfo.h"
#include "EventCursorLockInfo.h"
#include "PresenterSubscriber.h"

class PresenterSubject
{
public:
    virtual void NotifyOnRenderingProviderChanged(EventRenderingProviderInfo& e) = 0;
    virtual void NotifyOnAttributesChanged(EventAttributeInfo& e) = 0;
    virtual void NotifyOnAttributesRemoved(EventAttributeInfo& e) = 0;
    virtual void NotifyOnScaleUpdate(std::any src) = 0;
    virtual void NotifyOnRedraw(std::any src) = 0;
    virtual void NotifyOnClose(std::any src) = 0;
    virtual void NotifyOnLockCursorSizeChanged(EventResizeInfo& e) = 0;
    virtual void NotifyOnCursorLockStateChanged(EventCursorLockInfo& e) = 0;
    virtual void AddPresenterSubscriber(PresenterSubscriber* subscriber) = 0;
    virtual void RemovePresetnerSubscriber(PresenterSubscriber* subscriber) = 0;
};



#endif //LII_PRESENTERSUBJECT_H
