#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"
#include "Button.h"


class ButtonController : public KeyStateSubscriber
{
public:
    void OnKeyDown(EventKeyStateInfo e) override
    {
    }

    void OnKeyUp(EventKeyStateInfo e) override
    {

    }

    void OnKeyPressed(EventKeyStateInfo e) override
    {
        auto* button = dynamic_cast<Button*>(e.GetSource());
        if(static_cast<InputManager::VirtualKeys>(e.GetVirtualKey()) == InputManager::VirtualKeys::A)
        {
            button->SetWidth(button->GetWidth() - 10);
        }

        if(static_cast<InputManager::VirtualKeys>(e.GetVirtualKey()) == InputManager::VirtualKeys::D)
        {
            button->SetWidth(button->GetWidth() + 10);
        }
    }

public:


};

int main( int argc, char* argv[] )
{
//    int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto controller = ButtonController{};
    auto& button1 = window->CreateElement<Button>(50, 50, 100, 50, "button1");
    auto& button2 = window->CreateElement<Button>(50, 120, 100, 50, "button2");
    button1.SetText(L"Button 1");
    button2.SetText(L"Button 2");
    button1.AddKeyStateSubscriber(controller);
    button2.AddKeyStateSubscriber(controller);

    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}