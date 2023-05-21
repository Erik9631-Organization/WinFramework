//
// Created by erik9 on 5/14/2023.
//

#include <iostream>
#include <Injector.hpp>
#include "Core.h"
#include "ZBufferRegionValidator.h"

void ZBufferRegionValidator::OnCoreInit(const EventCoreLifecycleInfo &e)
{
    outputBuffer->OnCoreInit(e);
}

void ZBufferRegionValidator::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    outputBuffer->OnCoreStart(e);
    bufferSize = e.GetCore()->GetCombinedScreenSize();
    InitializeZBuffer();
}

void ZBufferRegionValidator::OnCoreStop(const EventCoreLifecycleInfo &e)
{
    outputBuffer->OnCoreStop(e);
}

void ZBufferRegionValidator::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{
    outputBuffer->OnCoreDestroy(e);
}

void ZBufferRegionValidator::DrawFragment(const glm::ivec3 &position, const glm::ivec4 &color)
{
    if(TestDiscardFragment(position))
        return;
    outputBuffer->DrawFragment(position, color);
}

void ZBufferRegionValidator::SwapScreenBuffer()
{
    ClearBuffer();
    outputBuffer->SwapScreenBuffer();
}

void ZBufferRegionValidator::SetViewportSize(const glm::ivec2 &size)
{
    outputBuffer->SetViewportSize(size);
}

void ZBufferRegionValidator::WriteToZBuffer(unsigned int x, unsigned int y, int value)
{
    if(IsOutsideBounds(x, y))
        return;
    if(zBuffer == nullptr)
        return;

    zBuffer[x + y * outputBuffer->GetViewportSize().x] = value;
}

void ZBufferRegionValidator::ReleaseZBuffer()
{
    delete zBuffer;
    zBuffer = nullptr;
}

ZBufferRegionValidator::ZBufferRegionValidator()
{
    try
    {
        outputBuffer = LiiInjector::Injector::GetInstance().ResolveTransient<BufferRenderer>();
    }
    catch (std::runtime_error& e)
    {
        std::cout <<"ZBufferRegionValidator BufferRenderer dependency injection failed with: "<< e.what() << std::endl;
    }

}

bool ZBufferRegionValidator::TestDiscardFragment(const glm::ivec3 &position)
{
    if(zBuffer == nullptr)
        return false;
    if(IsOutsideBounds(position.x, position.y))
        return true;

    if(position.x < 0 || position.y < 0 || position.x >= outputBuffer->GetViewportSize().x || position.y >= outputBuffer->GetViewportSize().y)
        return true;
    if(zBuffer[position.x + position.y * outputBuffer->GetViewportSize().x] < position.z)
        return true;
    WriteToZBuffer(position.x, position.y, position.z);
    return false;
}

void ZBufferRegionValidator::InitializeZBuffer()
{
    if(zBuffer != nullptr)
        ReleaseZBuffer();
    zBuffer = new int[bufferSize.x * bufferSize.y];
    ClearBuffer();
}

void ZBufferRegionValidator::ClearBuffer()
{
    if(zBuffer == nullptr)
        return;
    for(int i = 0; i < outputBuffer->GetViewportSize().x * outputBuffer->GetViewportSize().y; i++)
        zBuffer[i] = INT_MAX;
}

const glm::ivec2 &ZBufferRegionValidator::GetViewportSize() const
{
    return outputBuffer->GetViewportSize();
}

bool ZBufferRegionValidator::IsOutsideBounds(unsigned int x, unsigned int y)
{
    if(x >= outputBuffer->GetViewportSize().x || y >= outputBuffer->GetViewportSize().y)
        return true;
    return false;
}
