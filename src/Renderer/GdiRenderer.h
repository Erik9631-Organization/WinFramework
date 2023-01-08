//
// Created by Erik on 22/01/24.
//

#ifndef LII_GDIRENDERER_H
#define LII_GDIRENDERER_H
#include <Windows.h>
#include <gdiplus.h>
#pragma comment (lib, "Gdiplus.lib")
#include "Renderer.h"
#include "ResizeSubscriber.h"
#include "DrawData2D.h"
#include <functional>
#include <thread>
#include "Timer.h"
#include <mutex>
#include <condition_variable>
#include "UiTreeDataSyncer.h"
#include "Core.h"
#include "RenderingModel.h"
#include <map>

class Timer;
class WindowsCore;
class UiElement;
namespace Gdiplus
{
    class Region;
}

template<typename T> class MultiTree;


class GdiRenderer : public Renderer, public ResizeSubscriber
{
public:
    GdiRenderer();
    void Render() override;
    void OnResize(EventResizeInfo e) override;
    void OnInit(Core &coreWindowFrame) override;
    void OnDestroy(Core &coreWindow) override;
    std::unique_ptr<RenderingApi> AcquireRenderer() override;
    void SwapScreenBuffer() override;
    void AddModel(std::unique_ptr<RenderingModel> renderingModel) override;
    RenderingModel *GetModel(size_t index) override;
    const std::vector<std::unique_ptr<RenderingModel>> &GetRenderingModels() override;
    std::multimap<float, RenderingModel*> modelZIndexMap;
    std::vector<std::unique_ptr<RenderingModel>> renderingModels;

private:
    static void GdiStartup();
    static Gdiplus::GdiplusStartupOutput output;
    static ULONG token;

    WindowsCore* windowsCore;
    void AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node, Gdiplus::Region& clippingRegion);
    void CleanBackBuffer();
    HDC GetSecondaryDC();
    HWND windowHandle;
    HDC windowHdc;
    HDC secondaryDc;
    HBITMAP secondaryBitmap;
    std::condition_variable performRenderSignal;

};


#endif //LII_GDIRENDERER_H
