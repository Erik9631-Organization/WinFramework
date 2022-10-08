//
// Created by Erik on 08/10/22.
//

#include "CoreMediator.h"
#include "Window.h"
#include "RenderingProvider.h"
void CoreMediator::CoreOnDestroy(std::any src)
{

}

void CoreMediator::CoreOnClose(std::any src)
{

}

void CoreMediator::CoreOnMove(EventMoveInfo e)
{
    if(window == nullptr)
        return;
    window->SetPosition(e.GetPosition());
}

void CoreMediator::CoreOnResize(EventResizeInfo e)
{
    if(window == nullptr)
        return;
    window->SetSize(e.GetSize());
}

void CoreMediator::CoreOnMouseMove(EventMouseStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnMouseHover(e);
}

void CoreMediator::CoreOnMouseLButtonDown(EventMouseStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnMouseDown(e);
}

void CoreMediator::CoreOnMouseLButtonUp(EventMouseStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnMouseUp(e);
}

void CoreMediator::CoreOnMousePressed(EventMouseStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnMousePressed(e);
}


void CoreMediator::CoreOnKeyUp(EventKeyStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnKeyUp(e);
}

void CoreMediator::CoreOnKeyDown(EventKeyStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnKeyDown(e);
}
void CoreMediator::CoreOnKeyPressed(EventKeyStateInfo e)
{
    if(window == nullptr)
        return;
    window->NotifyOnKeyPressed(e);
}


/**
 * TODO Implement wheel events
 **/
void CoreMediator::CoreOnWheelMoved(EventKeyStateInfo e)
{

}

void CoreMediator::OnRenderingProviderChanged(EventRenderingProviderInfo &e)
{

}

void CoreMediator::OnAttributesChanged(EventAttributeInfo &e)
{
    core->SetAttributes(e.GetIndex(), e.GetValue());
}

void CoreMediator::OnAttributesRemoved(EventAttributeInfo &e)
{
    core->RemoveAttribute(e.GetIndex(), e.GetValue());
}

void CoreMediator::OnScaleUpdate(std::any src)
{
    core->UpdateScale();
}

void CoreMediator::OnRedraw(std::any src)
{
    core->Redraw();
}

void CoreMediator::OnClose(std::any src)
{
    core->Close();
}

void CoreMediator::OnLockCursorSizeChanged(EventResizeInfo &e)
{
    core->SetLockCursorSize(e.GetSize());
}

void CoreMediator::OnCursorLockStateChanged(EventCursorLockInfo &e)
{
    core->LockCursor(e.GetCursorLockInfo());
}

const bool CoreMediator::IsCursorLocked()
{
    return core->IsCursorLocked();
}

RenderingProvider * CoreMediator::OnRenderingProviderRequested()
{
    return core->GetRenderingProvider();
}
