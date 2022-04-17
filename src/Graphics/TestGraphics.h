//
// Created by Erik on 1/10/2022.
//

#ifndef GRAPHICS_TESTGRAPHICS_H
#define GRAPHICS_TESTGRAPHICS_H
#include "api/RenderCommander.h"
#include <Windows.h>
#include <gdiplus.h>
#include <Renderer.h>


class TestGraphics : public RenderCommander
{
private:
    std::vector<std::reference_wrapper<RenderCommander>> renderables;
public:
    TestGraphics();
    void Repaint() override;
    void AddRenderable(RenderCommander &renderable) override;
    void RemoveRenderable(RenderCommander &renderable) override;
    std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnRender(RenderEventInfo e) override;
};


#endif //GRAPHICS_TESTGRAPHICS_H
