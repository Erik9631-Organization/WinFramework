//
// Created by Erik on 1/10/2022.
//

#include "TestGraphics.h"
#include "RenderEventInfo.h"
#include "RenderingPool.h"

void TestGraphics::Repaint()
{

}

void TestGraphics::AddRenderCommander(RenderCommander &renderable)
{
    renderables.emplace_back(renderable);
}

void TestGraphics::RemoveRenderCommander(RenderCommander &renderable)
{

}

std::vector<std::reference_wrapper<RenderCommander>> TestGraphics::GetRenderables()
{
    return renderables;
}

void TestGraphics::OnRenderSync(RenderEventInfo e)
{
    ShapeRenderer& renderer = e.GetRenderer()->Acquire(*this);
    renderer.SetColor({0, 0, 0});
    renderer.SetThickness(0.1f);
    renderer.DrawRectangle({10, 10, 0}, {50, 50, 0});
}

TestGraphics::TestGraphics()
{

}
