//
// Created by erik9 on 12/7/2022.
//

#ifndef LII_DEMOAPPTEST_HPP
#define LII_DEMOAPPTEST_HPP
#include "DemoApplication.h"
#include "catch_amalgamated.hpp"
#include "ApplicationController.h"

TEST_CASE("Demo app test", "[demoApp]")
{
    DemoApplication::LaunchDemoApp();
    ApplicationController::GetApplicationController()->JoinThreads();
}


#endif //LII_DEMOAPPTEST_HPP