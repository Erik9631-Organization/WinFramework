//
// Created by erik9 on 5/14/2023.
//

#include "SoftwareRenderer.h"
#include "ConcurrentShapeRenderer.h"
#include <iostream>
#include <tracy/Tracy.hpp>

void SoftwareRenderer::OnCoreInit(const EventCoreLifecycleInfo &e)
{
    bufferRenderer->OnCoreInit(e);
}

void SoftwareRenderer::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    bufferRenderer->OnCoreStart(e);
}

void SoftwareRenderer::OnCoreStop(const EventCoreLifecycleInfo &e)
{
    bufferRenderer->OnCoreStop(e);
}

void SoftwareRenderer::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{
    bufferRenderer->OnCoreDestroy(e);
}

void SoftwareRenderer::Render()
{
    ZoneScoped;
    for (auto it = modelContainer.GetZIndexMap().rbegin(); it != modelContainer.GetZIndexMap().rend(); ++it)
        it->second->Draw();
}

RenderingModel *SoftwareRenderer::CreateModel(SubCommands createCommand)
{
    return modelContainer.CreateModel(createCommand);
}

RenderingModel *SoftwareRenderer::GetModel(size_t index)
{
    return modelContainer.GetModel(index);
}

void SoftwareRenderer::SwapScreenBuffer()
{
    bufferRenderer->SwapScreenBuffer();
}

void SoftwareRenderer::SetViewportSize(const glm::ivec2 &size)
{
    bufferRenderer->SetViewportSize(size);
}

SoftwareRenderer::SoftwareRenderer() :
    modelContainer(*this)
{
   // bufferRenderer = std::unique_ptr<BufferRenderer>(new ZBufferRegionValidator());
    try
    {
        bufferRenderer = LiiInjector::Injector::GetInstance().ResolveTransient<BufferRenderer>();
    }
    catch (std::runtime_error& e)
    {
        std::cout <<"ZBufferRegionValidator BufferRenderer dependency injection failed with: "<< e.what() << std::endl;
    }

}

const glm::ivec2 &SoftwareRenderer::GetViewportSize() const
{
    return bufferRenderer->GetViewportSize();
}

ShapeRenderer &SoftwareRenderer::AcquireShapeRenderer()
{
    auto& shapeRenderer = bufferRenderer->AcquireShapeRenderer();
    return shapeRenderer;
}
