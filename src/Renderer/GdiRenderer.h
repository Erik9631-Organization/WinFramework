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
#include "MoveSubscriber.h"


class Timer;
class WindowsCore;
class UiElement;
namespace Gdiplus
{
    class Region;
}

template<typename T> class MultiTree;


class GdiRenderer : public Renderer, public ResizeSubscriber, public MoveSubscriber
{
private:
    static void GdiStartup();
    static Gdiplus::GdiplusStartupOutput output;
    static ULONG token;

    WindowsCore* windowsCore;
    void CleanBackBuffer();
    HDC GetSecondaryDC();
    HWND windowHandle;
    HDC windowHdc;
    HDC secondaryDc;
    HBITMAP secondaryBitmap;
    std::multimap<float, RenderingModel*> modelZIndexMap;
    std::vector<std::unique_ptr<RenderingModel>> renderingModels;

    template<typename T>
    T* CreateModel()
    {
        auto model = std::make_unique<T>();
        model->SetRenderingProvider(this);
        return static_cast<T*>(AddModel(std::move(model)));
    }
    RenderingModel * AddModel(std::unique_ptr<RenderingModel> renderingModel);
public:
    void AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node, Gdiplus::Region& clippingRegion);
    GdiRenderer();
    void Render() override;
    void OnResize(EventResizeInfo e) override;
    void OnInit(Core &coreWindowFrame) override;
    void OnDestroy(Core &coreWindow) override;
    std::unique_ptr<RenderingApi> AcquireRenderingApi() override;
    void SwapScreenBuffer() override;
    RenderingModel *GetModel(size_t index) override;
    RenderingModel * CreateModel(Commands createCommand) override;

    void OnMove(EventMoveInfo e) override;
};


#endif //LII_GDIRENDERER_H
