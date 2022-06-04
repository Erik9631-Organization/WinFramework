#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include <Windows.h>
#include "DemoApplication.h"
#include "Window.h"
#include "OpenGLRenderingProvider.h"
#include "GraphicsShader.h"
#include "OnTickSubscriber.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "ActivateSubscriber.h"
#include "EventOnActivateInfo.h"
#include <iostream>
#include "ModelBuilder.h"
#include "Model.h"
#include <glm.hpp>
#include "GlobalResourceManager.h"
#include "ModeledElement.h"
#include "TextureManager.h"
#include "DefaultTexture.h"

using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController::Create(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    ApplicationController::GetApplicationController()->NotifyOnEntryStart();
	int returnVal = LiiEntry();
    ApplicationController::GetApplicationController()->NotifyOnEntryEnd();

	//Thread cleanup
    ApplicationController::GetApplicationController()->JoinThreads();
	return returnVal;
}



class CameraController : public OnTickSubscriber, public ActivateSubscriber
{

public:
    CameraController(Window& window) : window(window){}
    Window& window;
    const float speed = 0.001f;
    const float sensitivity = 0.15f;
    void OnTick() override
    {
        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::W))
        {
            OpenGL::CameraManager::GetActiveCamera()->Foward(speed);
        }

        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::S))
        {
            OpenGL::CameraManager::GetActiveCamera()->Backward(speed);
        }

        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::A))
        {
            OpenGL::CameraManager::GetActiveCamera()->Left(speed);
        }

        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::D))
        {
            OpenGL::CameraManager::GetActiveCamera()->Right(speed);
        }

        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::Escape))
        {
            window.LockCursor(false);
            window.SetActive(false);
        }

        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::LeftButton))
        {
            const Vector2& mousePos = InputManager::GetGlobalInput().GetMouseDelta();
            OpenGL::CameraManager::GetActiveCamera()->AddYaw(mousePos.GetX() * sensitivity);
            OpenGL::CameraManager::GetActiveCamera()->AddPitch(mousePos.GetY() * sensitivity);
        }

    }

    void OnActiveStateChanged(EventOnActivateInfo info) override
    {
        if(info.IsActive() == true)
        {
            //window.SetLockCursorSize({2, 2});
            //window.LockCursor(true);
        }
    }

};

int LiiEntry()
{
//    DemoApplication::LaunchDemoApp();
    Window* frame = new Window(0, 0, 800, 600, "TestFrame2");
    shared_ptr<OpenGLRenderingProvider> glProvider = make_shared<OpenGLRenderingProvider>();
    frame->SetRenderingProvider(static_pointer_cast<RenderingProvider>(glProvider));
    auto* manager = GlobalResourceManager::GetGlobalResourceManager().GetResourceManager<TextureManager>("texture");
    auto& texture = manager->CreateTexture<OpenGL::DefaultTexture>("WallTexture", "Textures\\wall.jpg", GL_RGB);
    texture.LoadResource();

    OpenGL::ModelBuilder builder3D{};
    OpenGL::ModelBuilder builder2D{};
    glm::mat4* projectionMatrix = new glm::mat4(glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 1000.0f));
    glm::mat4* orthographicMatrix = new glm::mat4(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, 100.0f));
    builder3D.SetProjectionMatrix(projectionMatrix);
    builder2D.SetProjectionMatrix(orthographicMatrix);
    std::unique_ptr<OpenGL::Model> wallBlock = builder3D.CreateBlock(0, 0, -50, 20.0f, 20.0f, 20.0f);
    std::unique_ptr<OpenGL::Model> block = builder3D.CreateBlock(40, 40, -50, 10.0f, 10.0f, 10.0f);
    std::unique_ptr<OpenGL::Model> rectangle = builder2D.CreateFillRectangle(50, 50, 50, 50);
    rectangle->Translate({0, 0, -10.0f});

    ModeledElement& wallBlockElement = frame->Create<ModeledElement>(std::move(wallBlock));
    //wallBlockElement.GetModel()->GetMaterial().SetColor({1.0f, 0.3f, 0.3f, 1.0f});

    ModeledElement& blockElement = frame->Create<ModeledElement>(std::move(block));
    blockElement.GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});

    rectangle->SetCamera(nullptr);
    rectangle->CustomCameraEnabled(false);
    auto& rectangleElement = frame->Create<ModeledElement>(std::move(rectangle));
    rectangleElement.GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});
    rectangleElement.GetModel()->GetMaterial().SetAmbient({1.0f, 1.0f, 1.0f});

    wallBlockElement.GetModel()->SetTexture(&texture);


    CameraController* controller = new CameraController{*frame};
    frame->AddOnTickSubscriber(controller);
    frame->AddOnActivateSubscriber(*controller);
	return 0;
}