//
// Created by Erik on 22/01/24.
//

#ifndef LII_GDIRENDERINGPROVIDER_H
#define LII_GDIRENDERINGPROVIDER_H
#include "RenderingProvider.h"
#include "ResizeSubscriber.h"
#include "DrawData2D.h"
#include <functional>
#include <thread>
#include "Timer.h"
#include <mutex>
#include <condition_variable>

class Timer;
class CoreWindow;
class UiElement;
namespace Gdiplus
{
    class Region;
}

template<typename T> class MultiTree;


class GdiRenderingProvider : public RenderingProvider, public ResizeSubscriber
{
public:
    GdiRenderingProvider();
    void Render() override;
    void OnResize(EventResizeInfo e) override;
    void OnInit(CoreWindow &coreWindowFrame) override;
    void OnDestroy(CoreWindow &coreWindow) override;
    void OnRemove(CoreWindow &coreWindow) override;
    void WaitForSyncToFinish() override;
    int GetTargetFps() const;
    void SetTargetFps(int targetFps);
    std::unique_ptr<std::thread> renderingThread;
private:
    CoreWindow* coreWindowframe;
    void AssignGraphicsToNodes(MultiTree<UiElement&>& node, Gdiplus::Region& clippingRegion);
    void CleanBackBuffer();
    void AssignGraphicsToNodes();
    [[noreturn]] void InternalRender();
    void SyncData(MultiTree<UiElement&>& node);
    HDC GetSecondaryDC();
    HWND windowHandle;
    HDC windowHdc;
    HDC secondaryDc;
    HBITMAP secondaryBitmap;
    DrawData2D defaultDrawData;
    int targetFps = 60;
    bool startRenderingLoop = true;
    Timer fpsTimer;

    bool performRender = false;
    bool syncFinished = true;
    std::condition_variable performRenderSignal;

    std::condition_variable syncFinishedSignal;

};


#endif //LII_GDIRENDERINGPROVIDER_H
