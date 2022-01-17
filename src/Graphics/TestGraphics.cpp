//
// Created by Erik on 1/10/2022.
//

#include "TestGraphics.h"
#include "RenderEventInfo.h"

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
    Gdiplus::RectF rect = Gdiplus::RectF(10, 10, 50, 50);
    e.GetGraphics()->DrawRectangle(pen, rect);
}

TestGraphics::TestGraphics()
{
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Blue);
    pen = new Gdiplus::Pen(brush);
    pen->SetWidth(0.1f);
}
