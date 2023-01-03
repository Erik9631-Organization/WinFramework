//
// Created by Erik on 22/01/24.
//

#ifndef LII_GDIRENDERINGPROVIDER_H
#define LII_GDIRENDERINGPROVIDER_H
#include <Windows.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")
#include "RenderingProvider.h"
#include "ResizeSubscriber.h"
#include "DrawData2D.h"
#include <functional>
#include <thread>
#include "Timer.h"
#include <mutex>
#include <condition_variable>
#include "UiTreeDataSyncer.h"
#include "Core.h"

class Timer;
class WindowsCore;
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
    void OnInit(Core &coreWindowFrame) override;
    void OnDestroy(Core &coreWindow) override;
    void OnRemove(Core &coreWindow) override;
    void WaitForSyncToFinish() override;
    int GetTargetFps() const;
    void SetTargetFps(int targetFps);

    std::unique_ptr<Renderer> AcquireRenderer() override;

    std::thread* renderingThread;
private:
    static void GdiStartup();
    static Gdiplus::GdiplusStartupOutput output;
    static ULONG token;

    UiTreeDataSyncer syncer;
    WindowsCore* windowsCore;
    void AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node, Gdiplus::Region& clippingRegion);
    void CleanBackBuffer();
    void AssignGraphicsToNodes();
    [[noreturn]] void InternalRender();
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
    std::condition_variable performRenderSignal;

};


#endif //LII_GDIRENDERINGPROVIDER_H
