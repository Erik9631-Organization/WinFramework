#include "ApplicationController.h"
#include "Window.h"
#include "WinWrapper.h" // Needed
#include "DemoApplication.h"
#include "OpenGLRenderingProvider.h"
#include "GraphicsShader.h"
#include "OnTickSubscriber.h"
#include "CameraManager.h"
//#include "InputManager.h"
#include "ActivateSubscriber.h"
#include "EventOnActivateInfo.h"
#include <iostream>
#include "ModelBuilder.h"
#include "Model.h"
#include <glm.hpp>
#include "GlobalResourceManager.h"
#include "ModeledElement.h"
#include "TextureManager.h"
#include "StaticTexture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
using namespace std;


int main()
{
    ApplicationController::Create();

    ApplicationController::GetApplicationController()->NotifyOnEntryStart();
	int returnVal = LiiEntry();
    ApplicationController::GetApplicationController()->NotifyOnEntryEnd();

	//Thread cleanup
    ApplicationController::GetApplicationController()->JoinThreads();
	return 0;
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


        if(InputManager::GetGlobalInput().IsKeyDown(InputManager::VirtualKeys::LeftButton))
        {
            const Vector2& mousePos = InputManager::GetGlobalInput().GetMouseDelta();
            OpenGL::CameraManager::GetActiveCamera()->AddYaw(mousePos.GetX() * sensitivity);
            OpenGL::CameraManager::GetActiveCamera()->AddPitch(mousePos.GetY() * sensitivity);
        }

    }

    void OnActiveStateChanged(EventOnActivateInfo info) override
    {

    }

};

class LightController : public OnTickSubscriber
{
public:

    LightController(PointLight& pointLight) : light(pointLight)
    {

    }
    void OnTick() override
    {
        glm::vec3 translation = light.GetTranslation();
        translation.z = currentTranslation;
        light.SetTranslation(translation);


        currentTranslation += translationValue;

        if(currentTranslation > translationMax)
            translationValue *= -1;
        if(currentTranslation < translationMax * -1)
            translationValue *= -1;
    }
private:
    float currentTranslation = 0.0f;
    float translationValue = 0.0005f;
    float translationMax = 100.0f;
    PointLight& light;

};

int LiiEntry()
{
    DemoApplication::LaunchDemoApp();
//    Window* frame = new Window(0, 0, 800, 600, "TestFrame2");
//    shared_ptr<OpenGLRenderingProvider> glProvider = make_shared<OpenGLRenderingProvider>();
//    frame->SetRenderingProvider(static_pointer_cast<RenderingProvider>(glProvider));
//
//
//
//    auto* manager = GlobalResourceManager::GetGlobalResourceManager().GetResourceManager<TextureManager>("texture");
//    auto& texture = manager->CreateTexture<OpenGL::StaticTexture>("WallTexture", "Textures\\wall.jpg", GL_RGB);
//    manager->LoadResource("WallTexture");
//    OpenGL::ModelBuilder builder3D{};
//    OpenGL::ModelBuilder builder2D{};
//    glm::mat4* projectionMatrix = new glm::mat4(glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 1000.0f));
//    glm::mat4* orthographicMatrix = new glm::mat4(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, 100.0f));
//    builder3D.SetProjectionMatrix(projectionMatrix);
//    builder2D.SetProjectionMatrix(orthographicMatrix);
//
//
//
//    std::unique_ptr<OpenGL::Model> wallBlock = builder3D.CreateBlock(0, 0, -50, 20.0f, 20.0f, 20.0f);
//    std::unique_ptr<OpenGL::Model> block = builder3D.CreateBlock(40, 40, -50, 10.0f, 10.0f, 10.0f);
//    block->GetMaterial().SetSpecular({0.5f, 0.5f, 0.5f});
//    std::unique_ptr<OpenGL::Model> rectangle = builder2D.CreateFillRectangle(50, 50, 100, 100);
//    rectangle->SetTranslation({0, 0, -10.0f});
//
//    ModeledElement& wallBlockElement = frame->CreateElement<ModeledElement>(std::move(wallBlock));
//
//    ModeledElement& blockElement = frame->CreateElement<ModeledElement>(std::move(block));
//    blockElement.GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});
//
//    rectangle->SetCamera(nullptr);
//    rectangle->CustomCameraEnabled(true);
//    auto& rectangleElement = frame->CreateElement<ModeledElement>(std::move(rectangle));
//    rectangleElement.GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});
//    rectangleElement.GetModel()->GetMaterial().SetAmbient({1.0f, 1.0f, 1.0f});
//
//    wallBlockElement.GetModel()->SetTexture("WallTexture");
//
//    DirectionalLight& light = frame->CreateElement<DirectionalLight>(std::move(builder3D.CreateEmptyModel()), glm::vec3{0.0f, 1.0f, 0.1f});
//    light.SetColor({64.0f/255.0f, 156.0f/255.0f, 1.0f, 1.0f});
//
//    auto pointLightModel = builder3D.CreateBlock(0, 0, 0, 5.0f, 5.0f, 5.0f);
//    auto& pointLight = frame->CreateElement<PointLight>(std::move(pointLightModel));
//    pointLight.GetModel()->GetMaterial().SetAmbient({1.0f, 1.0f, 1.0f});
//    pointLight.GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});
//    pointLight.SetColor({0.5f, 0.5f, 0.7f, 1.0f});
//    pointLight.SetTranslation({30.0f, 0.0f, 0.0f});
//
//
//    CameraController* controller = new CameraController{*frame};
//    frame->AddOnTickSubscriber(controller);
//    frame->AddOnActivateSubscriber(*controller);
//
//    LightController* lightController = new LightController(pointLight);
//
//    frame->AddOnTickSubscriber(lightController);
	return 0;
}