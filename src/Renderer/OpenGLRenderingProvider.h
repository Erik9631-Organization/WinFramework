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

class OpenGLRenderingProvider : public RenderingProvider
{
public:
    void Render() override;
    void OnInit(CoreWindow &coreWindowFrame) override;
    void OnDestroy(CoreWindow &coreWindow) override;
    void OnRemove(CoreWindow &coreWindow) override;
    void WaitForSyncToFinish() override;
private:
    void AssignGraphicsToNodes(MultiTree<UiElement&>& node);
    void GraphicsInit();
    void AssignRendererToNodes();
    void GetGlExtensions();
    void PrepareWindowRenderer(CoreWindow& window);
    HGLRC openGlContext;
    HDC windowDc;
    void InternalRender();
    bool startRenderingLoop = true;
    CoreWindow* coreWindow;
    std::unique_ptr<std::thread> renderingThread;
    bool performRender = false;
    std::condition_variable performRenderSignal;
    UiTreeDataSyncer uiSyncer;
    std::unique_ptr<OpenGLRenderingPool> renderingPool;
    void SyncTestData();

    //Used for default rendering if nothing else is specified
    std::unique_ptr<OpenGL::DefaultShaderProgram> defaultProgram;
    unsigned int shaderProgram;

    ///TestPurpose --- DELETE
    std::vector<std::unique_ptr<OpenGL::Model>> models;
    OpenGL::DefaultRenderingManager manager;
};


#endif //LII_OPENGLRENDERINGPROVIDER_H
