//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERER_H
#define LII_RENDERER_H
#include "RenderingApi.h"
#include "RenderingModel.h"
#include <vector>
#include "RenderMessage.h"
class Core;

class Renderer
{
public:
    virtual void Render() = 0;
    virtual RenderingModel * CreateModel(Commands createCommand) = 0;
    virtual RenderingModel* GetModel(size_t index) = 0;
    virtual void OnInit(Core &coreWindow) = 0;
    virtual void OnDestroy(Core &coreWindow) = 0;
    virtual void SwapScreenBuffer() = 0;
    virtual std::unique_ptr<RenderingApi> AcquireRenderingApi() = 0;
    virtual ~Renderer() = default;
};


#endif //LII_RENDERER_H
