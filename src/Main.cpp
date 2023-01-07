#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"

int main( int argc, char* argv[] )
{
    //int result = Catch::Session().run(argc, argv);
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    window->Repaint();
    ApplicationController::GetApplicationController()->JoinThreads();
    return 0;
}