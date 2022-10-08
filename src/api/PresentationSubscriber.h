//
// Created by Erik on 08/10/22.
//

#ifndef LII_PRESENTATIONSUBSCRIBER_H
#define LII_PRESENTATIONSUBSCRIBER_H
#include "RenderingProvider.h"
#include "EventRenderingProviderInfo.h"
#include "EventAttributeInfo.h"
#include "EventResizeInfo.h"
#include "EventCursorLockInfo.h"

class PresentationSubscriber
{
public:
    virtual void OnRenderingProviderChanged(EventRenderingProviderInfo& e) = 0;
    virtual void OnAttributesChanged(EventAttributeInfo& e) = 0;
    virtual void OnAttributesRemoved(EventAttributeInfo& e) = 0;
    virtual void OnScaleUpdate(std::any src) = 0;
    virtual void OnRedraw(std::any src) = 0;
    virtual void OnClose(std::any src) = 0;
    virtual void OnLockCursorSizeChanged(EventResizeInfo& e) = 0;
    virtual void OnCursorLockStateChanged(EventCursorLockInfo& e) = 0;
    virtual const bool IsCursorLocked() = 0;
    virtual RenderingProvider * OnRenderingProviderRequested() = 0;
};


#endif //LII_PRESENTATIONSUBSCRIBER_H
