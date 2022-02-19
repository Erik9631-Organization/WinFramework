//
// Created by Erik on 01/02/22.
//

#ifndef LII_OPENGLRENDERINGPROVIDER_H
#define LII_OPENGLRENDERINGPROVIDER_H
#include "RenderingProvider.h"
#include <Windows.h>
#include <memory>
#include <thread>
#include <mutex>
#include <DefaultShaderProgram.h>
#include "UiTreeDataSyncer.h"
#include "Mesh.h"
//#include "DefaultShaderProgram.h"


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
    void PreRender();
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

    //Used for default rendering if nothing else is specified
    std::unique_ptr<DefaultShaderProgram> defaultProgram;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int shaderProgram;

    ///TestPurpose --- DELETE
    std::vector<std::unique_ptr<Mesh>> meshes;
};


#endif //LII_OPENGLRENDERINGPROVIDER_H
