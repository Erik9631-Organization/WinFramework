#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"
#include "Button.h"


int main( int argc, char* argv[] )
{
//    int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto& button1 = window->CreateElement<Button>(50, 50, 100, 50, "button1");
    auto& button2 = window->CreateElement<Button>(50, 120, 100, 50, "button2");
    button1.SetText(L"Button 1");
    button2.SetText(L"Button 2");

    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}