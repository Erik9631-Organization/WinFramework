//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERINGPROVIDER_H
#define LII_RENDERINGPROVIDER_H
#include "Renderer.h"
#include "RenderingModel.h"
#include <vector>
class Core;

class RenderingProvider
{
public:
    virtual void Render() = 0;
    virtual void AddModel(std::unique_ptr<RenderingModel> renderingModel) = 0;
    virtual RenderingModel* GetModel(size_t index) = 0;
    virtual const std::vector<std::unique_ptr<RenderingModel>>& GetRenderingModels() = 0;
    virtual void OnInit(Core &coreWindow) = 0;
    virtual void OnDestroy(Core &coreWindow) = 0;
    virtual void OnRemove(Core &coreWindow) = 0;
    virtual void WaitForSyncToFinish() = 0;
    virtual void SwapScreenBuffer() = 0;
    virtual std::unique_ptr<Renderer> AcquireRenderer() = 0;
    virtual ~RenderingProvider() = default;
};


#endif //LII_RENDERINGPROVIDER_H
