//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_ZBUFFERREGIONVALIDATOR_H
#define LII_ZBUFFERREGIONVALIDATOR_H
#include "BufferRenderer.h"

class ZBufferRegionValidator : public BufferRenderer
{
private:
    int* zBuffer = nullptr;
    glm::ivec2 bufferSize{0};
    void WriteToZBuffer(unsigned int x, unsigned int y, int value);
    bool TestDiscardFragment(const glm::ivec3 &position);
    void ClearBuffer();
    void InitializeZBuffer();
    void ReleaseZBuffer();
    std::unique_ptr<BufferRenderer> outputBuffer = nullptr;
    bool IsOutsideBounds(unsigned int x, unsigned int y);
public:
    ZBufferRegionValidator();
    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

    void DrawFragment(const glm::ivec3 &position, const glm::ivec4 &color) override;

    void SwapScreenBuffer() override;

    void SetViewportSize(const glm::ivec2 &size) override;

    const glm::ivec2 &GetViewportSize() const override;

};


#endif //LII_ZBUFFERREGIONVALIDATOR_H
