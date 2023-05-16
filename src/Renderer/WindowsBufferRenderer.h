//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_WINDOWSBUFFERRENDERER_H
#define LII_WINDOWSBUFFERRENDERER_H
#include "BufferRenderer.h"
#include "Injectable.h"
#include "WindowsCore.h"
#include "BitmapManager.h"

class WindowsBufferRenderer : public BufferRenderer
{
private:
    BitmapManager* front;
    BitmapManager* back;
    WindowsCore* core = nullptr;
    HDC windowHdc = nullptr;
    HDC secondaryHdc = nullptr;
    glm::ivec2 viewportSize{0};
    void CreateGraphicsBuffer();
    void CreateSecondaryDc();
    void DeleteSecondaryDc();
    void CreateBitmap();
public:
    WindowsBufferRenderer();

    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

    void DrawFragment(const glm::ivec3 &position, const glm::ivec4 &color) override;

    void SwapScreenBuffer() override;

    void SetViewportSize(const glm::ivec2 &size) override;

    ~WindowsBufferRenderer() override;

};


#endif //LII_WINDOWSBUFFERRENDERER_H
