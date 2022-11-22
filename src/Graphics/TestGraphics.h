//
// Created by Erik on 1/10/2022.
//

#ifndef GRAPHICS_TESTGRAPHICS_H
#define GRAPHICS_TESTGRAPHICS_H
#include "RenderCommander.h"
#include <Renderer.h>


class TestGraphics : public RenderCommander
{
private:
    std::vector<std::reference_wrapper<RenderCommander>> renderables;
public:
    TestGraphics();
    void Repaint() override;
    void AddRenderCommander(RenderCommander &renderable) override;
    void RemoveRenderCommander(RenderCommander &renderable) override;
    std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnRenderSync(RenderEventInfo e) override;
};


#endif //GRAPHICS_TESTGRAPHICS_H
