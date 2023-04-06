#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"
#include "Button.h"


int main( int argc, char* argv[] )
{
//    int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    window->CreateElement<Button>(50, 50, 100, 50);
    window->CreateElement<Button>(50, 120, 100, 50);
    window->Repaint();
    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}