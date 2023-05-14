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

    std::unique_ptr<ShapeRenderer> AcquireShapeRenderer() override;
    void SwapScreenBuffer() override;
    RenderingModel *GetModel(size_t index) override;

    RenderingModel *CreateModel(SubCommands createCommand) override;

    void SetViewportSize(int width, int height) override;

    void SetViewportSize(const glm::ivec2 &size) override;

    void OnCoreInit(const EventCoreLifecycleInfo &e) override;

    void OnCoreStart(const EventCoreLifecycleInfo &e) override;

    void OnCoreStop(const EventCoreLifecycleInfo &e) override;

    void OnCoreDestroy(const EventCoreLifecycleInfo &e) override;

private:
    void AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node);
    void GraphicsInit();
    void AssignRendererToNodes();
    void GetGlExtensions();
    void PrepareWindowRenderer(WindowsCore& window);
    HGLRC openGlContext;
    HDC windowDc;
    void InternalRender();    bool startRenderingLoop = true;
    WindowsCore* windowsCore;
    std::thread* renderingThread;
    bool performRender = false;
    std::condition_variable performRenderSignal;
    std::unique_ptr<Element3dDataSyncer> element3dSyncer;
    std::unique_ptr<OpenGLRenderingPool> renderingPool;

    //Used for default rendering if nothing else is specified
    std::unique_ptr<OpenGL::DefaultShaderProgram> defaultProgram;
    unsigned int shaderProgram;

    ///TODO TestPurpose --- DELETE
    std::vector<std::unique_ptr<OpenGL::Model>> models;
    OpenGL::DefaultRenderingManager manager;
};


#endif //LII_OPENGLRENDERER_H
