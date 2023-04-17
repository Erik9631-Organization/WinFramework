#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"
#include "Button.h"


class ButtonController : public KeyStateSubscriber, public ResizeSubscriber
{
private:
    Button& button1;
    Button& button2;

public:
    ButtonController(Button& button1, Button& button2) : button1(button1), button2(button2)
    {
    }

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

    void OnResize(EventResizeInfo e) override
    {
        if(e.GetSize().x < 200)
        {
            button1.SetWidth(25);
            button2.SetWidth(25);
            return;
        }
        button1.SetWidth(100);
        button2.SetWidth(100);

    }


};

int main( int argc, char* argv[] )
{
//    int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");

    auto& button1 = window->CreateElement<Button>(50, 50, 100, 50, "button1");
    auto& button2 = window->CreateElement<Button>(50, 120, 100, 50, "button2");
    auto controller = ButtonController{button1, button2};
    window->AddOnResizeSubscriber(controller);
    button1.SetText(L"Button 1");
    button2.SetText(L"Button 2");
    button1.AddKeyStateSubscriber(controller);
    button2.AddKeyStateSubscriber(controller);

    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}