//
// Created by Erik on 01/02/22.
//

#include <Windows.h>
#include <gdiplus.h>
#include "OpenGLRenderingProvider.h"
#include <glew.h>
#include <wglew.h>
#include "ApplicationController.h"
#include <string>
#include "RenderEventInfo.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "ModelBuilder.h"
#include "StaticTexture.h"
#include "CameraManager.h"
#include "Model.h"
#include "EventUpdateInfo.h"
#include "ShaderManager.h"
#include "GraphicsShader.h"
#include "GlobalResourceManager.h"
#include "Window.h"
#include "Core/Windows/WindowsCore.h"
#include <iostream>



void OpenGLRenderingProvider::Render()
{
    performRender = true;
    performRenderSignal.notify_one();
}

void OpenGLRenderingProvider::OnInit(Core &coreWindowFrame)
{
    ApplicationController::GetApplicationController()->AddEntryStateSubscriber(this);
    this->windowsCore = dynamic_cast<WindowsCore*>(&coreWindowFrame);
    if(this->windowsCore == nullptr)
    {
        /*TODO ADD LOGGING*/
        //Exit the application with an error
    }
    GetGlExtensions();
    //now create openGlWindow
    PrepareWindowRenderer(*windowsCore);
    renderingPool = std::make_unique<OpenGLRenderingPool>(*windowsCore->GetWrapperFrame(), manager);
    element3dSyncer = std::make_unique<Element3dDataSyncer>(*renderingPool);
    GraphicsInit();
    renderingThread = &ApplicationController::GetApplicationController()->CreateThread([=]{InternalRender();}, to_string((long long)this)+"renderThread");
}


void OpenGLRenderingProvider::PrepareWindowRenderer(WindowsCore& window)
{
    int pixelFormat[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB , 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };

    windowDc = GetDC(window.GetWindowHandle());
    int matchingIndex = 0;
    unsigned int matchingSize = 0;
    bool pWglChoosePixelFormatARBStatus = wglChoosePixelFormatARB(windowDc, pixelFormat, NULL, 1, &matchingIndex, &matchingSize);
    if(!pWglChoosePixelFormatARBStatus || !matchingSize)
    {
        std::cout << "wglChoosePixelFormatARB failed with error: " << GetLastError() << endl;
        system("PAUSE");
        exit(0);
    }

    PIXELFORMATDESCRIPTOR  formatDescription;
    if(!DescribePixelFormat(windowDc, matchingIndex, sizeof(PIXELFORMATDESCRIPTOR), &formatDescription))
    {
        std::cout << "Failed to describe pixel format!" << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    if(!SetPixelFormat(windowDc, matchingIndex, &formatDescription))
    {
       std::cout << "Failed to set pixel format!" << to_string(GetLastError()) << std::endl;
       system("PAUSE");
       exit(0);
    }


    int glContextAttrib[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    openGlContext = wglCreateContextAttribsARB(windowDc, 0, glContextAttrib);

    if(!openGlContext)
    {
        std::cout << "Failed creating GL context with error: " << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    if(!wglMakeCurrent(windowDc, openGlContext))
    {
        std::cout << "Error selecting gl context" << std::endl;
        exit(0);
    }
    std::string test{(LPCSTR)glGetString(GL_VERSION)};
    SetWindowText(window.GetWindowHandle(), test.c_str());

    glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(windowDc);
}

void OpenGLRenderingProvider::GetGlExtensions()
{
    //CreateElement dummy window
    WNDCLASSA dummyWindowClass;
    ZeroMemory(&dummyWindowClass, sizeof(WNDCLASSA));
    dummyWindowClass.hInstance = GetModuleHandleA(NULL);
    dummyWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    dummyWindowClass.lpfnWndProc = DefWindowProcA;
    dummyWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    dummyWindowClass.lpszClassName = "Dummy window";


    if(!RegisterClass(&dummyWindowClass))
    {
        std::cout << "Register dummy Class error: " << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    HWND dummyHandle = CreateWindow("Dummy window", NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                    CW_USEDEFAULT, NULL, NULL, GetModuleHandleA(NULL), NULL);
    if(!dummyHandle)
    {
        std::cout << "Error creating dummy window handle" << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }
    HDC windowHdc = GetDC(dummyHandle);
    PIXELFORMATDESCRIPTOR pixelDescription;
    pixelDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDescription.nVersion = 1;
    pixelDescription.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelDescription.iPixelType = PFD_TYPE_RGBA;
    pixelDescription.cColorBits = 32;
    pixelDescription.cDepthBits = 24;
    pixelDescription.cAlphaBits = 8;
    int pixelFormatIndex = ChoosePixelFormat(windowHdc, &pixelDescription);
    if(!pixelFormatIndex)
    {
        std::cout << "Error creating dummy pixel format index" << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    if(!SetPixelFormat(windowHdc, pixelFormatIndex, &pixelDescription))
    {
        std::cout << "Error setting dummy pixel format index" << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    HGLRC glContext = wglCreateContext(windowHdc);
    if(!glContext)
    {
        std::cout << "Error creating dummy openGL rendering context" << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }

    if(!wglMakeCurrent(windowHdc, glContext))
    {
        std::cout << "Error selecting dummy gl context" << std::endl;
        exit(0);
    }

    GLenum result = glewInit();
    if(result != GLEW_OK)
    {
        std::cout << "Error loading extentions" << std::endl;
        exit(0);
    }

    wglMakeCurrent(nullptr, nullptr); // release current
    wglDeleteContext(glContext);
    ReleaseDC(dummyHandle, windowHdc);
    DeleteDC(windowHdc);
    DestroyWindow(dummyHandle);
}

void OpenGLRenderingProvider::OnDestroy(Core &coreWindow)
{
    auto* core = dynamic_cast<WindowsCore*>(&coreWindow);
    if(core == nullptr)
    {
        /*TODO ADD LOGGING*/
        //Exit the application with an error
    }
    ReleaseDC(core->GetWindowHandle(), GetDC(core->GetWindowHandle()));
    startRenderingLoop = false;
    renderingThread->join();

}

void OpenGLRenderingProvider::OnRemove(Core &coreWindow)
{

}

void OpenGLRenderingProvider::WaitForSyncToFinish()
{
    uiSyncer.WaitForSync();
    if(element3dSyncer != nullptr)
        element3dSyncer->WaitForSync();
}

void OpenGLRenderingProvider::InternalRender()
{
    ApplicationController::GetApplicationController()->WaitForEntryToFinish();
    wglMakeCurrent(windowDc, openGlContext);
    Window* window = windowsCore->GetWrapperFrame();
    glEnable(GL_DEPTH_TEST);
    while(startRenderingLoop)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mutex lockMutex;
        std::unique_lock<std::mutex>performRenderLock(lockMutex);
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        ///TODO Thread sync problem
        //Wait for update could finish and another cycle could start before uiSyncer sends a signal. Mutex is requried here.
        windowsCore->WaitForUpdateToFinish();
        uiSyncer.SyncData(windowsCore->GetWrapperFrame()->GetUiElementNode());
        element3dSyncer->SyncData(windowsCore->GetWrapperFrame()->Get3dScene().GetElementNode());
        if(window == nullptr)
            continue;
        glViewport(0, 0, window->GetWidth(), window->GetHeight()); // Update the viewport
        AssignRendererToNodes();
        manager.Render();
        performRender = !windowsCore->IsEventBased();
        SwapBuffers(windowDc);
    }
}


void OpenGLRenderingProvider::AssignRendererToNodes()
{
    Window* wrapperFrame = windowsCore->GetWrapperFrame();
    if(wrapperFrame == nullptr)
        return;
    AssignGraphicsToNodes(wrapperFrame->GetUiElementNode());
}

void OpenGLRenderingProvider::AssignGraphicsToNodes(MultiTree<unique_ptr<UiElement>> &node)
{
    if(!node.IsRoot())
        renderingPool->SetTranslation(node.GetValue()->GetPosition());
    else
        renderingPool->SetTranslation({0, 0});

    RenderEventInfo renderEvent{renderingPool.get()};
    node.GetValue()->OnRenderSync(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        AssignGraphicsToNodes(node.GetNode(i));
    }

}

void OpenGLRenderingProvider::GraphicsInit()
{
    //CreateElement default shaders
    ShaderProgram& program = GlobalResourceManager::GetGlobalResourceManager().GetResourceManager<ShaderManager>("shader")->
        CreateShaderProgram<OpenGL::DefaultShaderProgram>("default");

    program.AssembleShader(std::make_unique<OpenGL::GraphicsShader>(L"Shaders/default.frag", GL_FRAGMENT_SHADER));
    program.AssembleShader(std::make_unique<OpenGL::GraphicsShader>(L"Shaders/default.vert", GL_VERTEX_SHADER));
    program.Link();


//    OpenGL::ShapeBuilder builder;
//    float screenWidth = 800;
//    float screenHeight = 600;
//    auto projection2D = std::make_shared<glm::mat4>
//    (
//        2.0f/screenWidth, 0, 0, -1,
//        0, -2.0f/screenHeight, 0, 1,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    );
//    *projection2D = glm::transpose(*projection2D);
//    glm::mat4* projectionMatrix = new glm::mat4(glm::perspective(glm::radians(45.0f), screenWidth/screenHeight, 0.1f, 1000.0f));
//
//    builder.SetProjectionMatrix(projectionMatrix);
//    auto wallBlock = builder.CreateBlock(0, 100, 0, 20.0f, 20.0f, 20.0f);
//    auto texture = new OpenGL::DefaultTexture("Textures/wall.jpg", GL_RGB);
//    if(texture->LoadFromFile() == false)
//        CoreWindow::ConsoleWrite("Texture load failed!");
//    texture->LoadResource();
//    wallBlock->SetTexture(texture);
//    auto block = builder.CreateBlock(40, 40, -50, 10.0f, 10.0f, 10.0f);
//
//    //rectangle->Translate({0.0f, 0.0f, -10.0f});
//    //rectangle->Rotate(-55.0f, {1.0f, 0.0f, 0.0f});
//
//   // auto triangle = builder.CreateTriangle({0, 0}, {100, 125}, {100, 175});
//    //triangle->ResetTransform();
//    //triangle->Translate({0, 0, 0});
//
//    manager.AddModel(*wallBlock);
//    manager.AddModel(*block);
//    models.emplace_back(std::move(block));
//    models.emplace_back(std::move(wallBlock));
//    models.at(0)->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});
}

void OpenGLRenderingProvider::OnEntryStart()
{

}

void OpenGLRenderingProvider::OnEntryEnd()
{
    wglMakeCurrent(nullptr, nullptr);
}

