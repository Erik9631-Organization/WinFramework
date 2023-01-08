//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERER_H
#define LII_OPENGLRENDERER_H
#include "Renderer.h"
#include "UiTreeDataSyncer.h"
#include "Element3dDataSyncer.h"

class OpenGLRenderer : public Renderer
{
public:
    void Render() override;
    void OnInit(Core &coreWindowFrame) override;
    void OnDestroy(Core &coreWindow) override;

    std::unique_ptr<RenderingApi> AcquireRenderingApi() override;
    void SwapScreenBuffer() override;
    void AddModel(std::unique_ptr<RenderingModel> renderingModel) override;
    RenderingModel *GetModel(size_t index) override;
    const std::vector<std::unique_ptr<RenderingModel>> &GetRenderingModels() override;

private:
    void AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node);
    void GraphicsInit();
    void AssignRendererToNodes();
    void GetGlExtensions();
    void PrepareWindowRenderer(WindowsCore& window);
    HGLRC openGlContext;
    HDC windowDc;
    void InternalRender();
    bool startRenderingLoop = true;
    WindowsCore* windowsCore;
    std::thread* renderingThread;
    bool performRender = false;
    std::condition_variable performRenderSignal;
    std::unique_ptr<Element3dDataSyncer> element3dSyncer;
    std::unique_ptr<OpenGLRenderingPool> renderingPool;

    //Used for default rendering if nothing else is specified
    std::unique_ptr<OpenGL::DefaultShaderProgram> defaultProgram;
    unsigned int shaderProgram;

    ///TestPurpose --- DELETE
    std::vector<std::unique_ptr<OpenGL::Model>> models;
    OpenGL::DefaultRenderingManager manager;
};


#endif //LII_OPENGLRENDERER_H
