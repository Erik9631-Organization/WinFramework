//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_SOFTWARERENDERER_H
#define LII_SOFTWARERENDERER_H


#include "Renderer.h"
#include "ModelContainer.h"
#include "BufferRenderer.h"

class SoftwareRenderer : public Renderer
{
private:
    ModelContainer modelContainer;
    std::unique_ptr<BufferRenderer> bufferRenderer;
public:
    SoftwareRenderer();
    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

    void Render() override;

    RenderingModel *CreateModel(SubCommands createCommand) override;

    RenderingModel *GetModel(size_t index) override;

    void SwapScreenBuffer() override;

    void SetViewportSize(const glm::ivec2 &size) override;

    [[nodiscard]] const glm::ivec2 &GetViewportSize() const override;

    ShapeRenderer &AcquireShapeRenderer() override;

};


#endif //LII_SOFTWARERENDERER_H
