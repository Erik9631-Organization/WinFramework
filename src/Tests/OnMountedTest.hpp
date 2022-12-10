//
// Created by erik9 on 12/7/2022.
//
#include "catch_amalgamated.hpp"
#include "ApplicationController.h"
#include "Window.h"
class TestComponent : public UiElement
{
private:
    unsigned int onMountedCallCount = 0;
public:
    using UiElement::UiElement;
    void OnMounted(Presenter &presenter) override
    {
        onMountedCallCount++;
    }

    const unsigned int& GetNumberOfOnMountedCalls() const
    {
        return onMountedCallCount;
    }

};



TEST_CASE("Mounted event one component", "[mountedEvent1]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto& testElement1 = window->CreateElement<TestComponent>("component1");
    REQUIRE(testElement1.GetNumberOfOnMountedCalls() == 1);
    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();
}

TEST_CASE("Mounted event multiple components in a tree", "[mountedEvent2]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto& testElement1 = window->CreateElement<TestComponent>("component1");
    auto& testElement2 = testElement1.CreateElement<TestComponent>("Component2");
    auto& testElement3 = testElement1.CreateElement<TestComponent>("component3");
    auto& testElement4 = testElement2.CreateElement<TestComponent>("component4");

    SECTION("Multiple components test")
    {
        REQUIRE(testElement1.GetNumberOfOnMountedCalls() == 1);
        REQUIRE(testElement2.GetNumberOfOnMountedCalls() == 1);
        REQUIRE(testElement3.GetNumberOfOnMountedCalls() == 1);
        REQUIRE(testElement4.GetNumberOfOnMountedCalls() == 1);
    }

    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();

}