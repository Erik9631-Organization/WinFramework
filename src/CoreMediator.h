//
// Created by Erik on 08/10/22.
//

#ifndef LII_COREMEDIATOR_H
#define LII_COREMEDIATOR_H
#include "CoreSubscriber.h"
#include "PresenterSubscriber.h"
#include "Presenter.h"
#include "Core.h"
#include "AsyncRenderCommandHandler.h"
class Window;

class CoreMediator : public CoreSubscriber, public PresenterSubscriber
{
private:
    Presenter* presenter = nullptr;
    std::unique_ptr<Core> core = nullptr;
    void SetupPresenter(Presenter* presenter);
    void SetupCore(std::unique_ptr<Core> core);
public:
    CoreMediator();
    CoreMediator(Presenter* presenter, std::unique_ptr<Core> core);
    void SetPresenter(Presenter* presenter);
    void SetCore(std::unique_ptr<Core> core);
    void CoreOnDestroy(std::any src) override;
    void CoreOnClose(std::any src) override;
    void CoreOnMove(EventMoveInfo e) override;
    void CoreOnResize(EventResizeInfo e) override;
    void CoreOnMouseMove(EventMouseStateInfo e) override;
    void CoreOnMouseLButtonDown(EventMouseStateInfo e) override;
    void CoreOnMouseLButtonUp(EventMouseStateInfo e) override;
    void CoreOnKeyUp(EventKeyStateInfo e) override;
    void CoreOnKeyDown(EventKeyStateInfo e) override;
    void CoreOnKeyPressed(EventKeyStateInfo e) override;
    void CoreOnWheelMoved(EventKeyStateInfo e) override;
    void CoreOnMousePressed(EventMouseStateInfo e) override;
    void OnRenderingProviderChanged(EventRenderingProviderInfo &e) override;
    void OnAttributesChanged(EventAttributeInfo &e) override;
    void OnAttributesRemoved(EventAttributeInfo &e) override;
    void OnScaleUpdate(std::any src) override;
    void Redraw(std::any src) override;
    void OnClose(std::any src) override;
    void OnLockCursorSizeChanged(EventResizeInfo &e) override;
    void OnCursorLockStateChanged(EventCursorLockInfo &e) override;
    const bool IsCursorLocked() override;
    AsyncRenderCommandHandler * GetRenderer();
};


#endif //LII_COREMEDIATOR_H
