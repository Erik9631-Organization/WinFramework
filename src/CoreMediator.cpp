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
    if(presenter == nullptr)
        return;
    presenter->SetPosition(e.GetPosition(), false);
}

void CoreMediator::CoreOnResize(EventResizeInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->SetSize(e.GetSize(), false);
}

void CoreMediator::CoreOnMouseMove(EventMouseStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnMouseHover(e);
}

void CoreMediator::CoreOnMouseLButtonDown(EventMouseStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnMouseDown(e);
}

void CoreMediator::CoreOnMouseLButtonUp(EventMouseStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnMouseUp(e);
}

void CoreMediator::CoreOnMousePressed(EventMouseStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnMousePressed(e);
}


void CoreMediator::CoreOnKeyUp(EventKeyStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnKeyUp(e);
}

void CoreMediator::CoreOnKeyDown(EventKeyStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnKeyDown(e);
}
void CoreMediator::CoreOnKeyPressed(EventKeyStateInfo e)
{
    if(presenter == nullptr)
        return;
    presenter->NotifyOnKeyPressed(e);
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
    if(core == nullptr)
        return;
    core->SetAttributes(e.GetIndex(), e.GetValue());
}

void CoreMediator::OnAttributesRemoved(EventAttributeInfo &e)
{
    if(core == nullptr)
        return;
    core->RemoveAttribute(e.GetIndex(), e.GetValue());
}

void CoreMediator::OnScaleUpdate(std::any src)
{
    if(core == nullptr)
        return;
    core->UpdateScale();
}

void CoreMediator::OnRedraw(std::any src)
{
    if(core == nullptr)
        return;
    core->Redraw();
}

void CoreMediator::OnClose(std::any src)
{
    if(core == nullptr)
        return;
    core->Close();
}

void CoreMediator::OnLockCursorSizeChanged(EventResizeInfo &e)
{
    if(core == nullptr)
        return;
    core->SetLockCursorSize(e.GetSize());
}

void CoreMediator::OnCursorLockStateChanged(EventCursorLockInfo &e)
{
    if(core == nullptr)
        return;
    core->LockCursor(e.GetCursorLockInfo());
}

const bool CoreMediator::IsCursorLocked()
{
    if(core == nullptr)
        return false;
    return core->IsCursorLocked();
}

RenderingProvider * CoreMediator::GetRenderingProvider()
{
    if(core == nullptr)
        return nullptr;
    return core->GetRenderingProvider();
}

void CoreMediator::SetPresenter(Presenter *presenter)
{
    SetupPresenter(presenter);
}

void CoreMediator::SetCore(unique_ptr<Core> core)
{
    SetupCore(std::move(core));
}

void CoreMediator::WaitForRenderingSyncToFinish()
{
    core->WaitForRenderingSyncToFinish();
}

CoreMediator::CoreMediator(Presenter* presenter, std::unique_ptr<Core> core)
{
    SetupCore(std::move(core));
    SetupPresenter(presenter);
}

CoreMediator::CoreMediator()
{

}

void CoreMediator::SetupPresenter(Presenter *presenter)
{
    this->presenter = presenter;
    presenter->AddPresenterSubscriber(this);
}

void CoreMediator::SetupCore(std::unique_ptr<Core> core)
{
    this->core = std::move(core);
    this->core->AddCoreSubscriber(this);
}