//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERINGPROVIDER_H
#define LII_OPENGLRENDERINGPROVIDER_H
#include <Windows.h>
#include "RenderingProvider.h"
#include <memory>
#include <thread>
#include <mutex>
#include <DefaultShaderProgram.h>
#include "UiTreeDataSyncer.h"
#include "Model.h"
#include "OpenGLRenderingPool.h"
#include "DefaultRenderingManager.h"
#include "Element3dDataSyncer.h"

class OpenGLRenderingProvider : public RenderingProvider
{
public:
    void Render() override;
    void OnInit(Core &coreWindowFrame) override;
    void OnDestroy(Core &coreWindow) override;
    void OnRemove(Core &coreWindow) override;
    void WaitForSyncToFinish() override;
    void OnEntryStart() override;
    void OnEntryEnd() override;
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
    WindowsCore* coreWindow;
    std::thread* renderingThread;
    bool performRender = false;
    std::condition_variable performRenderSignal;
    UiTreeDataSyncer uiSyncer;
    std::unique_ptr<Element3dDataSyncer> element3dSyncer;
    std::unique_ptr<OpenGLRenderingPool> renderingPool;

    //Used for default rendering if nothing else is specified
    std::unique_ptr<OpenGL::DefaultShaderProgram> defaultProgram;
    unsigned int shaderProgram;

    ///TestPurpose --- DELETE
    std::vector<std::unique_ptr<OpenGL::Model>> models;
    OpenGL::DefaultRenderingManager manager;
};


#endif //LII_OPENGLRENDERINGPROVIDER_H
