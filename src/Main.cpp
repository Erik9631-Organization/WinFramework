#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"
#include "Button.h"
#include "RadioButton.h"
#include "Checkbox.h"
#include "Label.h"
#include "TextInput.h"
#include "PasswordField.h"
#include "ScrollBar.h"
#include "Grid.h"


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
            auto size = button->GetSize();
            size.y -= 10;
            button->SetSize(size);
        }

        if(static_cast<InputManager::VirtualKeys>(e.GetVirtualKey()) == InputManager::VirtualKeys::D)
        {
            auto size = button->GetSize();
            size.y += 10;
            button->SetSize(size);
        }
    }

    void OnResize(EventResizeInfo e) override
    {
        if(e.GetSize().x < 200)
        {
            auto size1 = button1.GetSize();
            auto size2 = button2.GetSize();
            size1.x = 25;
            size2.x = 25;

            button1.SetSize(size1);
            button2.SetSize(size2);
            return;
        }
        button1.SetSize({100, button1.GetSize().y, button1.GetSize().z});
        button2.SetSize({100, button2.GetSize().y, button2.GetSize().z});

    }


};

int main( int argc, char* argv[] )
{
//    int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
     auto& button1 = window->CreateElement<Button>(50, 50, 100, 50, "button1");
     auto pos = button1.GetPosition();
     pos.z = -100;
     button1.SetPosition(pos);
    auto& button2 = window->CreateElement<Button>(50, 120, 100, 50, "button2");
    auto& radioButton1 = window->CreateElement<RadioButton>(50, 190, 100, 50, "radioButton1");
    auto& radioButton2 = window->CreateElement<RadioButton>(50, 260, 100, 50, "radioButton2");
    auto& checkBox1 = window->CreateElement<Checkbox>(50, 330, 100, 50, "checkBox1");
    auto& label1 = window->CreateElement<Label>(50, 400, 100, 50, "checkBox1");
    auto& textInput = window->CreateElement<TextInput>(200, 0, 200, 100, "textInput");
    window->CreateElement<PasswordField>(200, 170, 200, 100, "passwordField");
    textInput.SetMultiline(true);
    checkBox1.SetText(L"Checkbox 1");
    label1.SetText(L"Label 1");
    auto ellipseProxy = std::make_unique<EllipseProxy>();
    window->GetRenderer()->RequestModel(*ellipseProxy);
    ellipseProxy->SetFill(true);
    ellipseProxy->SetColor({255, 0, 0, 255});
    ellipseProxy->SetSize({50, 50, 0});
    ellipseProxy->SetPosition({0, 0, -1});
    auto controller = ButtonController{button1, button2};
    window->AddOnResizeSubscriber(controller);
    button1.SetText(L"Button 1");
    button2.SetText(L"Button 2");
    radioButton1.SetText(L"Radio Button 1");
    radioButton2.SetText(L"Radio Button 2");
    radioButton2.AddToGroup(radioButton1);
    button1.AddKeyStateSubscriber(controller);
    button2.AddKeyStateSubscriber(controller);

    auto scrollbar = std::make_unique<ScrollBar>(0, 0, 10, 0, "ScrollBar");
    auto& panel = window->CreateElement<Panel>(470, 0, 300, 250, "panel");
    ScrollBar::Control(panel, std::move(scrollbar));

    for (int i = 0; i < 10; i++)
    {
        auto scrollBarTest = std::make_unique<Label>(0, 10 + 110 * i, 100, 100, "testLabel");

        scrollBarTest->SetText(L"TestLabel " + std::to_wstring(i));
        panel.Add(std::move(scrollBarTest));
    }

    auto mainTestGrid = std::make_unique<Grid>(800, 10, 500, 500);
    mainTestGrid->SetGridColumns({ 100, 400 });
    mainTestGrid->SetGridRows({ 100, 300, 100 });
    mainTestGrid->SetColumnGap(2);
    mainTestGrid->SetRowGap(2);
    mainTestGrid->AddRowSpan(0, 2);

    auto contentGrid = std::make_unique<Grid>(0, 0, 0, 0);
    contentGrid->SetRowGap(2);
    contentGrid->SetGridColumns({ 100, 100, 100, 100 });
    contentGrid->SetDefaultRowSize(100);


    auto header = std::make_unique<Label>(0, 0, 0, 0, "header");
    header->SetText(L"header");

    auto footer = std::make_unique<Label>(0, 0, 0, 0, "footer");
    footer->SetText(L"footer");

    auto content = std::make_unique<Label>(0, 0, 0, 0, "content");
    content->SetText(L"content");

    auto navBar = std::make_unique<Label>(0, 0, 0, 0, "navBar");
    navBar->SetText(L"navBar");


    mainTestGrid->Add(std::move(navBar));
    mainTestGrid->Add(std::move(header));
    auto& ContentGridRef = *contentGrid;
    mainTestGrid->Add(std::move(contentGrid));
    mainTestGrid->Add(std::move(footer));
    ContentGridRef.Add(std::move(content));

    for (int i = 0; i < 11; i++)
    {
        auto contentLabel = std::make_unique<Label>(0, 0, 100, 100, "ContentLabel" + std::to_string(i));
        ContentGridRef.Add(std::move(contentLabel));
    }

    window->Add(std::move(mainTestGrid));


    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}