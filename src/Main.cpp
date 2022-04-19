#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include <Windows.h>
#include "DemoApplication.h"
#include "Window.h"
#include "OpenGLRenderingProvider.h"
#include "GraphicsShader.h"
#include "Button.h"
#include "OnTickSubscriber.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "ActivateSubscriber.h"
#include "EventOnActivateInfo.h"
#include "FloatVertexAttribute.h"
#include <iostream>
#include "ModelBuilder.h"
#include "Model.h"
#include <glm.hpp>
#include "ModeledElement.h"

using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    controller.NotifyOnStart();
	int returnVal = LiiEntry();

	//Thread cleanup
	ApplicationController::JoinThreads();

	return returnVal;
}

/*
* TODO
* 1) Add OnActionEvent for buttons
* 2) Repaint not being used on pure renderable components. Investigate better design --- interface pollution
*	A) Repaint should notify the parent component which in return should send a repaint request
* 3) Create a global event class that has event src as parameter. All events MUST derive from that
* 9) Input is propagated by the root to whoever has the focus. To make the design consistent, each component should propagate the input to its subcomponents. The component recieving
*	 The event should then decide whether it should notify the subscribers or not (Based on IsFocus). Revisit this design and improve.
* 11) Make graphical element properties consistent
* 12) Renderables lack visibility option.
* 13) Renderables should have rendering order
* 14) Checkbox should be a graphical component on its own, similar to radio thumbTrack
* 17) Behaviors should have setters and getters. They are strategy pattern and they should be run time hot swapable
* 20) Fix InternalOffset calls causing massive slow down (Internal position calls Element position which causes updates, this is temporarily disabled for the sake of functionality)
*		Should be removed entirely. The offsets should be handled by the matrix you fucking moron
* 21) Duplicate methods. "Listener methods" leftover in the components. 
* 22) Wrap grid into a builder. The parameters should not be changed after the grid is created. Explore other options making it possible.
* 23) Finish collision checking so invalid spans can't be added to the grid --- done, grid should only call the method now.
* 24) Fix event GetSrc generics. Some return components some return any and some return your custom made generic type. Explore if it is necessary and try to avoid it.
*
* Optimization
* 1) Create rendering queve and rendering request class which specifies the rendering source. Each class should have an ID (Either real or pregenerated from the type)
*	 The rendering queve should be handled by the root and it should limit the maximum amount of renders to 30 repaints per second
* 2) Combobox memory leaks
* 3) Use multimedia windows timers. Standard timers are too slow and inaccurate causing the FPS to fluctuate. TEMP FIX: Uncap the FPS
* 
* Design
* 1) Remove generics from all the events and send the src as subject by default. The inheritance hierarchy will allow you to cast it to the correct type. Src is ALWAYS a subject.
* 2) All the behaviors should be covered by a common interface to be able to make them hot swappable. (It is not going to be completely possible, but at least create a common interface for the same behavioral groups)
* 3) ListBox and combobox
*		1) Both have internal factories that generate the elements. Give an option to place any factory inside the components so any element can be part of it.
* 4) !IMPORTANT! Sync improvement. Add a SendSyncData function to the UiElement (GameObj as well), which allows user to specify his custom data that the component will receive
*    during a sync. The target should be known by Id. Both UiElement (GameObj as well) will need to generate their instance Ids during the start.
 *    The DrawData should be renamed to SyncData. They should have an ID to know what kind of data is used.
* 
* Bugs
 * 1) Sometimes the window closes but the process doesn't. Can be observed as console stays open and the window closes
*/


/** TODO Refactor
 * Modify transform of the components based on scrollbar position
 */

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
    Window* frame = new Window(0, 0, 800, 600, "TestFrame");
    shared_ptr<OpenGLRenderingProvider> glProvider = make_shared<OpenGLRenderingProvider>();
    frame->SetRenderingProvider(static_pointer_cast<RenderingProvider>(glProvider));

    OpenGL::ModelBuilder builder{};
    glm::mat4* projectionMatrix = new glm::mat4(glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 1000.0f));
    builder.SetProjectionMatrix(projectionMatrix);
    std::unique_ptr<OpenGL::Model> wallBlock = builder.CreateBlock(0, 0, -50, 20.0f, 20.0f, 20.0f);
    std::unique_ptr<OpenGL::Model> block = builder.CreateBlock(40, 40, -50, 10.0f, 10.0f, 10.0f);
    ModeledElement* wallBlockElement = new ModeledElement(std::move(wallBlock));
    wallBlockElement->GetModel()->GetMaterial().SetColor({1.0f, 0.3f, 0.3f, 1.0f});
    ModeledElement* blockElement = new ModeledElement(std::move(block));
    blockElement->GetModel()->GetMaterial().SetColor({1.0f, 1.0f, 1.0f, 1.0f});

    frame->Add(wallBlockElement);
    frame->Add(blockElement);


    CameraController controller{*frame};
    frame->AddOnTickSubscriber(&controller);
    frame->AddOnActivateSubscriber(controller);

	ApplicationController::JoinThreads();
	return 0;
}