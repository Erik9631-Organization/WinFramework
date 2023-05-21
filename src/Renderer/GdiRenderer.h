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
#include "Timer.h"
#include <condition_variable>
#include "UiTreeDataSyncer.h"
#include "Core.h"
#include "RenderingModel.h"
#include <map>
#include "MoveSubscriber.h"
#include <condition_variable>
#include "TextModel.h"
#include "ModelContainer.h"


class Timer;
class WindowsCore;
class UiElement;
namespace Gdiplus
{
    class Region;
}

template<typename T> class MultiTree;


class GdiRenderer : public Renderer
{
private:
    static void GdiStartup();
    static Gdiplus::GdiplusStartupOutput output;
    static ULONG token;

    WindowsCore* windowsCore = nullptr;
    void DeleteSecondaryDc();
    void UpdateBitmap();
    void CreateSecondaryDc();
    HWND windowHandle = nullptr;
    HDC windowHdc = nullptr;
    HDC secondaryDc = nullptr;
    HBITMAP screenBitmap = nullptr;
    glm::ivec2 viewPortSize{0};
    ModelContainer modelContainer;
    std::vector<ShapeRenderer*> shapeRenderers;
    void ReleaseRenderers();
public:
    GdiRenderer();
    void Render() override;
    void SwapScreenBuffer() override;
    RenderingModel *GetModel(size_t index) override;
    RenderingModel * CreateModel(SubCommands createCommand) override;

    void SetViewportSize(const glm::ivec2 &size) override;

    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

    const glm::ivec2 &GetViewportSize() const override;

    ShapeRenderer &AcquireShapeRenderer() override;
};


#endif //LII_GDIRENDERER_H
