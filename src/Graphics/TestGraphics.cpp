//
// Created by Erik on 1/10/2022.
//

#include "TestGraphics.h"
#include "RenderEventInfo.h"
#include "Vector3.h"
#include "RenderingPool.h"

void TestGraphics::Repaint()
{

}

void TestGraphics::AddRenderable(RenderCommander &renderable)
{
    renderables.emplace_back(renderable);
}

void TestGraphics::RemoveRenderable(RenderCommander &renderable)
{

}

std::vector<std::reference_wrapper<RenderCommander>> TestGraphics::GetRenderables()
{
    return renderables;
}

void TestGraphics::OnRender(RenderEventInfo e)
{
    Renderer& renderer = e.GetRenderer()->Acquire(*this);
    renderer.SetColor({0, 0, 0});
    renderer.SetThickness(0.1f);
    renderer.DrawRectangle(10, 10, 50, 50);
}

TestGraphics::TestGraphics()
{

}
