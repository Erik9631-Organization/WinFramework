//
// Created by erik9 on 12/7/2022.
//
#include "catch_amalgamated.hpp"
#include "ApplicationController.h"
#include "Window.h"
#include "MountedSubscriber.h"

class TestComponent : public UiElement
{
private:
    unsigned int onMountedCallCount = 0;
public:
    using UiElement::UiElement;
    void OnMounted(Presenter &presenter, UiElement& element) override
    {
        onMountedCallCount++;
    }

    const unsigned int& GetNumberOfOnMountedCalls() const
    {
        return onMountedCallCount;
    }

};

class OnMountedSubscriber : public MountedSubscriber
{
private:
    unsigned int onMountedCallCount = 0;
public:
    void OnMounted(Presenter &presenter, UiElement& element) override
    {
        onMountedCallCount++;
    }

    const unsigned int& GetNumberOfOnMountedCalls() const
    {
        return onMountedCallCount;
    }
};


TEST_CASE("Mounted event test with subscriber and custom component", "[mountedEventSubscriber2][mountedEvents]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto mountedComponent = std::make_unique<TestComponent>("testComponent1");
    auto subscriber = OnMountedSubscriber{};
    mountedComponent->AddOnMountedSubscriber(subscriber);

    CHECK(subscriber.GetNumberOfOnMountedCalls() == 0);
    window->Add(std::move(mountedComponent));
    CHECK(subscriber.GetNumberOfOnMountedCalls() == 1);

    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();
}


TEST_CASE("Mounted event one subscriber test", "[mountedEventSubscriber1][mountedEvents]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto subscriber = OnMountedSubscriber{};
    window->AddOnMountedSubscriber(subscriber);
    CHECK(subscriber.GetNumberOfOnMountedCalls() == 1);
    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();
}


TEST_CASE("Mounted event one component", "[mountedEvent1][mountedEvents]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto& testElement1 = window->CreateElement<TestComponent>("component1");
    CHECK(testElement1.GetNumberOfOnMountedCalls() == 1);
    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();
}

TEST_CASE("Mounted event multiple components in a tree", "[mountedEvent2][mountedEvents]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto& testElement1 = window->CreateElement<TestComponent>("component1");
    auto& testElement2 = testElement1.CreateElement<TestComponent>("Component2");
    auto& testElement3 = testElement1.CreateElement<TestComponent>("component3");
    auto& testElement4 = testElement2.CreateElement<TestComponent>("component4");

    SECTION("Multiple components test")
    {
        CHECK(testElement1.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement2.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement3.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement4.GetNumberOfOnMountedCalls() == 1);
    }

    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();

}

TEST_CASE("Mounted event multiple components, added last", "[mountedEvent3][mountedEvents]")
{
    auto window = Window::Create(0, 0, 800, 600, "testWindow");
    auto testElement1 = std::make_unique<TestComponent>("component1");
    auto& testElement2 = testElement1->CreateElement<TestComponent>("Component2");
    auto& testElement3 = testElement1->CreateElement<TestComponent>("component3");
    auto& testElement4 = testElement2.CreateElement<TestComponent>("component4");

    auto& testElementRef = dynamic_cast<TestComponent&>(window->Add(std::move(testElement1)));

    SECTION("Multiple components test")
    {
        CHECK(testElementRef.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement2.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement3.GetNumberOfOnMountedCalls() == 1);
        CHECK(testElement4.GetNumberOfOnMountedCalls() == 1);
    }

    window->CloseWindow();
    ApplicationController::GetApplicationController()->JoinThreads();
}