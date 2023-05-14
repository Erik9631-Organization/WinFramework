//
// Created by Erik on 08/10/22.
//

#ifndef LII_CORE_H
#define LII_CORE_H
#include "AsyncRenderCommandHandler.h"
#include "CoreSubject.h"
#include "ResizeSubscriber.h"
#include "Injectable.h"
#include "CoreLifecycleSubject.h"
#include <memory>

class Window;

class Core : public CoreSubject, public LiiInjector::Injectable, public CoreLifecycleSubject
{
public:
    virtual void SetRenderer(std::unique_ptr<AsyncRenderCommandHandler> provider) = 0;
    virtual long long int SetAttributes(int index, long long int parameter) = 0;
    virtual long long int RemoveAttribute(int index, long long int parameter) = 0;
    virtual void UpdateScale() = 0;
    virtual void ScheduleRedraw() = 0;
    virtual void ForceRedraw() = 0;
    virtual void Close() = 0;
    virtual void SetWindow(Window* window) = 0;
    virtual void Start() = 0;
    virtual void SetLockCursorSize(const glm::vec3 &size) = 0;
    virtual void LockCursor(const bool& lockState) = 0;
    virtual const bool& IsCursorLocked() const = 0;
    virtual AsyncRenderCommandHandler * GetRenderer() = 0;
    virtual void AddOnResizePreProcessSubsriber(ResizeSubscriber& subscriber) = 0;
    virtual void RemoveOnResizePreProcessSubsriber(ResizeSubscriber& subscriber) = 0;
    virtual ~Core() = default;
};


#endif //LII_CORE_H
