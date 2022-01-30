//
// Created by Erik on 1/10/2022.
//

#ifndef GRAPHICS_TESTGRAPHICS_H
#define GRAPHICS_TESTGRAPHICS_H
#include "Renderable.h"
#include <Windows.h>
#include <gdiplus.h>
#include <Renderer.h>


class TestGraphics : public Renderable
{
private:
    std::vector<std::reference_wrapper<Renderable>> renderables;
public:
    TestGraphics();
    void Repaint() override;
    void AddRenderable(Renderable &renderable) override;
    void RemoveRenderable(Renderable &renderable) override;
    std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
    void OnRender(RenderEventInfo e) override;
};


#endif //GRAPHICS_TESTGRAPHICS_H
