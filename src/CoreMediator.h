//
// Created by Erik on 08/10/22.
//

#ifndef LII_COREMEDIATOR_H
#define LII_COREMEDIATOR_H
#include "CoreSubscriber.h"
#include "PresenterSubscriber.h"
#include "Presenter.h"
#include "Core.h"
class Window;

/**
 * TODO refactor so it meets names of existing interfaces
 */

class CoreMediator : public CoreSubscriber, public PresenterSubscriber
{
private:
    Presenter* window = nullptr;
    Core* core = nullptr;
public:
    void SetPresenter(Presenter* presenter);
    void SetCore(Core* core);
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
    void OnRedraw(std::any src) override;
    void OnClose(std::any src) override;
    void OnLockCursorSizeChanged(EventResizeInfo &e) override;
    void OnCursorLockStateChanged(EventCursorLockInfo &e) override;
    const bool IsCursorLocked() override;
    RenderingProvider * GetRenderingProvider() override;
};


#endif //LII_COREMEDIATOR_H