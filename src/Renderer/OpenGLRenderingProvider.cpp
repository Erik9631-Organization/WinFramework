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
#include "OpenGLRenderingPool.h"

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
    float color = 0.01f;
    while(startRenderingLoop)
    {
        mutex lockMutex;
        std::unique_lock<std::mutex>performRenderLock(lockMutex);
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        coreWindow->WaitForUpdateToFinish();

        //CoreWindow::ConsoleWrite("Syncing data!");
        uiSyncer.SyncData(coreWindow->GetWrapperFrame().GetUiElementNode());
        //CoreWindow::ConsoleWrite("Syncing done");
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        defaultProgram->Use();
        defaultProgram->GetUniformManager().SetUniform(glUniform4f, "color", color, 0.1f, 0.0f, 1.0f);
        for(std::unique_ptr<Mesh>& mesh : meshes)
            mesh->Draw();

        color+= 0.001f;
        if(color >= 1.0f)
            color = 0.0f;

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
    {
        //glTranslatef(node.GetValue().GetY(), node.GetValue().GetY(), 0);
    }

    //RenderEventInfo renderEvent{&renderer};
   // node.GetValue().OnRender(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        AssignGraphicsToNodes(node.Get(i));
    }

}

void OpenGLRenderingProvider::PreRender()
{
    defaultProgram = std::make_unique<DefaultShaderProgram>();
    defaultProgram->Add<GraphicsShader>(L"Shaders//default.frag", GL_FRAGMENT_SHADER);
    defaultProgram->Add<GraphicsShader>(L"Shaders//default.vert", GL_VERTEX_SHADER);

    if(!defaultProgram->Link())
    {
        CoreWindow::ConsoleWrite("Linking program failed!");
        return;
    }

    std::unique_ptr<DefaultMesh> shape1 = std::make_unique<DefaultMesh>(3, std::vector<float>{
        0.2f, 0.2f, 0.0f,
        0.2f, 0.4f, 0.0f,
        0.4f, 0.4f, 0.0f,
        0.4f, 0.2f, 0.0f,

    });
    shape1->SetVerticeDrawOrder(
    {
        0, 1, 3,
        1, 2, 3
    });

    std::unique_ptr<DefaultMesh> shape2 = std::make_unique<DefaultMesh>(3, std::vector<float>{
        0.4f, 0.4f, 0.0f,
        0.4f, 0.6f, 0.0f,
        0.6f, 0.6f, 0.0f,
        0.6f, 0.4f, 0.0f,

        });
    shape2->SetVerticeDrawOrder(
        {
            0, 1, 3,
            1, 2, 3
        });

    meshes.emplace_back(std::move(shape1));
    meshes.emplace_back(std::move(shape2));
}

