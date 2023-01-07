//
// Created by erik9 on 12/7/2022.
//

#ifndef LII_DEMOAPPTEST_HPP
#define LII_DEMOAPPTEST_HPP
#include "DemoApplication.h"
#include "catch_amalgamated.hpp"
#include "ApplicationController.h"
#include "Window.h"

TEST_CASE("Demo app test", "[demoApp]")
{
    DemoApplication::LaunchDemoApp();
    ApplicationController::GetApplicationController()->JoinThreads();
}

TEST_CASE("Basic background test", "[backgroundTest]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    window->Repaint();
    ApplicationController::GetApplicationController()->JoinThreads();
}

#endif //LII_DEMOAPPTEST_HPP
