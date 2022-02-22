//
// Created by Erik on 01/02/22.
//

#include "OpenGLRenderingProvider.h"
#include <Windows.h>
#include <glew.h>
#include <wglew.h>
#include "ApplicationController.h"
#include "CoreWindow.h"
#include <string>
#include "OpenGLRenderer.h"
#include "RenderEventInfo.h"
#include "GraphicsShader.h"
#include "DefaultMesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "DefaultModel.h"
#include "Shape2DBuilder.h"

void OpenGLRenderingProvider::Render()
{
    performRender = true;
    performRenderSignal.notify_one();
}

void OpenGLRenderingProvider::OnInit(CoreWindow &coreWindowFrame)
{
    GetGlExtensions();
    //now create openGlWindow
    PrepareWindowRenderer(coreWindowFrame);
    coreWindow = &coreWindowFrame;
    renderingThread = std::make_unique<std::thread>([=]{InternalRender();});
    renderingPool = std::make_unique<OpenGLRenderingPool>(coreWindow->GetWrapperFrame());
}

void OpenGLRenderingProvider::PrepareWindowRenderer(CoreWindow& window)
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
        CoreWindow::ConsoleWrite("wglChoosePixelFormatARB failed with error: " + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    PIXELFORMATDESCRIPTOR  formatDescription;
    if(!DescribePixelFormat(windowDc, matchingIndex, sizeof(PIXELFORMATDESCRIPTOR), &formatDescription))
    {
        CoreWindow::ConsoleWrite("Failed to describe pixel format!" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    if(!SetPixelFormat(windowDc, matchingIndex, &formatDescription))
    {
        CoreWindow::ConsoleWrite("Failed to set pixel format!" + to_string(GetLastError()));
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
        CoreWindow::ConsoleWrite("Failed creating GL context with error: " + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    if(!wglMakeCurrent(windowDc, openGlContext))
    {
        CoreWindow::ConsoleWrite("Error selecting gl context");
        exit(0);
    }
    std::string test{(LPCSTR)glGetString(GL_VERSION)};
    SetWindowText(window.GetWindowHandle(), test.c_str());

    glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(windowDc);
    wglMakeCurrent(nullptr, nullptr);
}

void OpenGLRenderingProvider::GetGlExtensions()
{
    //Create dummy window
    WNDCLASSA dummyWindowClass;
    ZeroMemory(&dummyWindowClass, sizeof(WNDCLASSA));
    dummyWindowClass.hInstance = ApplicationController::GetWinEntryArgs().hInstance;
    dummyWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    dummyWindowClass.lpfnWndProc = DefWindowProcA;
    dummyWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    dummyWindowClass.lpszClassName = "Dummy window";


    if(!RegisterClass(&dummyWindowClass))
    {
        CoreWindow::ConsoleWrite("Register dummy Class error: " + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    HWND dummyHandle = CreateWindow("Dummy window", NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                    CW_USEDEFAULT, NULL, NULL, ApplicationController::GetWinEntryArgs().hInstance, NULL);
    if(!dummyHandle)
    {
        CoreWindow::ConsoleWrite("Error creating dummy window handle" + to_string(GetLastError()));
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
        CoreWindow::ConsoleWrite("Error creating dummy pixel format index" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    if(!SetPixelFormat(windowHdc, pixelFormatIndex, &pixelDescription))
    {
        CoreWindow::ConsoleWrite("Error setting dummy pixel format index" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }

    HGLRC glContext = wglCreateContext(windowHdc);
    if(!glContext)
    {
        CoreWindow::ConsoleWrite("Error creating dummy openGL rendering context" + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }
    if(!wglMakeCurrent(windowHdc, glContext))
    {
        CoreWindow::ConsoleWrite("Error selecting dummy gl context");
        exit(0);
    }
    GLenum result = glewInit();
    if(result != GLEW_OK)
    {
        CoreWindow::ConsoleWrite("Error loading extentions");
        exit(0);
    }

    wglMakeCurrent(nullptr, nullptr); // release current
    wglDeleteContext(glContext);
    ReleaseDC(dummyHandle, windowHdc);
    DeleteDC(windowHdc);
    DestroyWindow(dummyHandle);
}

void OpenGLRenderingProvider::OnDestroy(CoreWindow &coreWindow)
{
    ReleaseDC(coreWindow.GetWindowHandle(), GetDC(coreWindow.GetWindowHandle()));
    startRenderingLoop = false;
    renderingThread->join();

}

void OpenGLRenderingProvider::OnRemove(CoreWindow &coreWindow)
{

}

void OpenGLRenderingProvider::WaitForSyncToFinish()
{
    uiSyncer.WaitForSync();
}

void OpenGLRenderingProvider::InternalRender()
{
    wglMakeCurrent(windowDc, openGlContext);
    PreRender();
    Window& window = coreWindow->GetWrapperFrame();
    while(startRenderingLoop)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mutex lockMutex;
        std::unique_lock<std::mutex>performRenderLock(lockMutex);
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        coreWindow->WaitForUpdateToFinish();
        uiSyncer.SyncData(coreWindow->GetWrapperFrame().GetUiElementNode());
        glViewport(0, 0, window.GetWidth(), window.GetHeight());
        AssignRendererToNodes();

        /*for(unique_ptr<Model>& model : models)
        {
            model->GetShader().GetUniformManager().SetUniform(glUniform4f, "color", 1.0f, 1.0f, 1.0f, 1.0f);
            model->Draw();
        }*/

        performRender = !coreWindow->IsEventBased();
        SwapBuffers(windowDc);
    }
}

void OpenGLRenderingProvider::AssignRendererToNodes()
{
    Window& wrapperFrame = coreWindow->GetWrapperFrame();
    AssignGraphicsToNodes(wrapperFrame.GetUiElementNode());
}

void OpenGLRenderingProvider::AssignGraphicsToNodes(MultiTree<UiElement &> &node)
{
    if(!node.IsRoot())
        renderingPool->SetTranslation(node.GetValue().GetPosition());
    else
        renderingPool->SetTranslation({0, 0});

    /**
     * TODO breaking RAII here. Ensure that either uniq_ptr is passed or reference
     */
    RenderEventInfo renderEvent{renderingPool.get()};
    node.GetValue().OnRender(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        AssignGraphicsToNodes(node.Get(i));
    }

}

void OpenGLRenderingProvider::PreRender()
{
    Shape2DBuilder builder;
    float screenWidth = 800;
    float screenHeight = 600;
    std::shared_ptr<glm::mat4> viewMatrix = std::make_shared<glm::mat4>
    (
        2.0f/screenWidth, 0, 0, -1,
        0, -2.0f/screenHeight, 0, 1,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
    *viewMatrix = glm::transpose(*viewMatrix);
    builder.SetViewMatrix(viewMatrix);

   // auto triangle = builder.CreateTriangle({0, 0}, {100, 125}, {100, 175});
    //triangle->ResetTransform();
    //triangle->Translate({0, 0, 0});
    models.emplace_back(builder.CreateRectangle(0, 0, 800, 600));
}

