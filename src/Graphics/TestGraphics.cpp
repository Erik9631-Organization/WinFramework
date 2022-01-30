//
// Created by Erik on 1/10/2022.
//

#include "TestGraphics.h"
#include "RenderEventInfo.h"
#include "Vector3.h"

void TestGraphics::Repaint()
{

}

void TestGraphics::AddRenderable(Renderable &renderable)
{
    renderables.emplace_back(renderable);
}

void TestGraphics::RemoveRenderable(Renderable &renderable)
{

}

std::vector<std::reference_wrapper<Renderable>> TestGraphics::GetRenderables()
{
    return renderables;
}

void TestGraphics::OnRender(RenderEventInfo e)
{
    e.GetRenderer()->SetColor({0, 0, 0});
    e.GetRenderer()->SetThickness(0.1f);
    e.GetRenderer()->DrawRectangle(10, 10, 50, 50);
}

TestGraphics::TestGraphics()
{

}
