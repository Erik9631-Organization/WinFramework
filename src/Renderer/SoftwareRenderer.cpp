//
// Created by erik9 on 5/14/2023.
//

#include "SoftwareRenderer.h"
#include "ConcurrentShapeRenderer.h"
#include <iostream>
#include "ZBufferRegionValidator.h"
#include <Tracy.hpp>

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
    for (auto& model : modelContainer.GetModels())
        model->Draw();
}

RenderingModel *SoftwareRenderer::CreateModel(SubCommands createCommand)
{
    return modelContainer.CreateModel(createCommand);
}

RenderingModel *SoftwareRenderer::GetModel(size_t index)
{
    return modelContainer.GetModel(index);
}

std::unique_ptr<ShapeRenderer> SoftwareRenderer::AcquireShapeRenderer()
{
    auto shapeRenderer = std::make_unique<ConcurrentShapeRenderer>(*bufferRenderer);
    return shapeRenderer;
}

void SoftwareRenderer::SwapScreenBuffer()
{
    bufferRenderer->SwapScreenBuffer();
    FrameMark;
}

void SoftwareRenderer::SetViewportSize(const glm::ivec2 &size)
{
    bufferRenderer->SetViewportSize(size);
}

SoftwareRenderer::SoftwareRenderer() :
    modelContainer(*this)
{
    bufferRenderer = std::unique_ptr<BufferRenderer>(new ZBufferRegionValidator());
}

const glm::ivec2 &SoftwareRenderer::GetViewportSize() const
{
    return bufferRenderer->GetViewportSize();
}
