//
// Created by Erik on 01/02/22.
//

#include "OpenGLRenderingProvider.h"
#include <Windows.h>
#include <glew.h>
#include <wglew.h>
#include <gl/gl.h>
#include "ApplicationController.h"
#include "CoreWindow.h"
#include <string>
#include "OpenGLRenderer.h"
#include "RenderEventInfo.h"

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
        CoreWindow::ConsoleWrite("pWglChoosePixelFormatARB failed with error: " + to_string(GetLastError()));
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
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
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

//    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
//    if(!wglCreateContextAttribsARB)
//    {
//        CoreWindow::ConsoleWrite("Error getting pWglCreateContextAttribsARB" );
//        system("PAUSE");
//        exit(0);
//    }
//    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
//
//    if(!wglChoosePixelFormatARB)
//    {
//        CoreWindow::ConsoleWrite("Error getting wglChoosePixelFormatARB" + to_string(GetLastError()));
//        system("PAUSE");
//        exit(0);
//    }

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
    syncer.WaitForSync();
}

void OpenGLRenderingProvider::InternalRender()
{
    wglMakeCurrent(windowDc, openGlContext);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        CoreWindow::ConsoleWrite( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        CoreWindow::ConsoleWrite("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        CoreWindow::ConsoleWrite("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    while(startRenderingLoop)
    {
        mutex lockMutex;
        std::unique_lock<std::mutex>performRenderLock(lockMutex);
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        coreWindow->WaitForUpdateToFinish();

        CoreWindow::ConsoleWrite("Syncing data!");
        syncer.SyncData(coreWindow->GetWrapperFrame().GetUiElementNode());
        CoreWindow::ConsoleWrite("Syncing done");
        /////////////////Rendering
        // -----
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        ////////////Rendering end
        //AssignRendererToNodes();
        SwapBuffers(windowDc);
        performRender = !coreWindow->IsEventBased();
        SwapBuffers(windowDc);
    }
}

void OpenGLRenderingProvider::AssignRendererToNodes()
{


    /*Window& wrapperFrame = coreWindow->GetWrapperFrame();
    AssignGraphicsToNodes(wrapperFrame.GetUiElementNode());*/
}

void OpenGLRenderingProvider::AssignGraphicsToNodes(MultiTree<UiElement &> &node)
{
    OpenGLRenderer renderer{};
    if(!node.IsRoot())
    {
        glTranslatef(node.GetValue().GetY(), node.GetValue().GetY(), 0);
    }

    RenderEventInfo renderEvent{&renderer};
    node.GetValue().OnRender(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        AssignGraphicsToNodes(node.Get(i));
    }

}
