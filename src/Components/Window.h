#pragma once
#include <Windows.h>
#include <condition_variable>
#include <string>
#include "Components/UiElement.h"
#include <vector>
#include "Events/MoveSubscriber.h"
#include "Events/ResizeSubscriber.h"
#include "Graphics/Background.h"
#include "GdiRenderingProvider.h"
#include "Scene.h"

using namespace std;
class CoreWindow;
class RenderingProvider;
/**
 * This class wraps the CoreWindow class and is responsible for delegating most of the method calls to that class.
 * It is also the top root of the containment hierarchy and is the first component that should be created in your application.
 * All the components that are to be displayed within the window should be added via the UiElement::Add function which this class inherits.
 */
class Window : public UiElement
{
private:
	UiElement* currentFocus = nullptr;
	UiElement* currentCapture = nullptr;
	CoreWindow* coreFrame = nullptr;
	thread* windowThread = nullptr;
	condition_variable* initWait = nullptr;
	bool initNotified = false;
	Background background;
	void CreateCoreWindow(LONG style);
	std::shared_ptr<RenderingProvider> renderingProvider;
    Scene scene3d;
public:
    void SetLockCursorSize(const Vector2& size);
    void LockCursor(const bool& lockState);
    const bool& IsCursorLocked() const;

	/**
	 * Adds a new flag to the window style. Some of these styles can not be changed at runtime. Please refer to <a href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlonga">MSDN</a>
	 * \param styleFlags the flag of the style you would like to add. List of flags are available here: <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles">MSDN</a>
	 */
	void AddWindowStyle(LONG styleFlags);
	/**
	 * Removes a flag to the window style. Some of these styles can not be changed at runtime. Please refer to <a href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlonga">MSDN</a>
	 * \param styleFlags the flag of the style you would like to remove. List of flags are available here: <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles">MSDN</a>
	 */
	void RemoveWindowStyle(LONG styleFlags);

	/**
	 * Adds a new flag to the window style.
	 * \param styleFlags the flag of the style you would like to add. List of flags are available here: <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles">MSDN</a>
	 */
	void AddWindowExtendedStyle(LONG styleFlags);

	/**
	 * Removes a flag to the window style.
	 * \param styleFlags the flag of the style you would like to remove. List of flags are available here: <a href="https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles">MSDN</a>
	 */
	void RemoveWindowExtendedStyle(LONG styleFlags);

	
	bool initDone = false;

	void SetSize(float width, float height) override;
	void SetSize(Vector2 size) override;
	void Repaint() override;
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vector2 point) override;

	virtual void NotifyOnKeyDown(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) override;
	void CloseWindow();

	void UpdateWindow();
	Window(std::string windowName);
	Window(int x, int y, int width, int height, std::string windowName);
	Window(int x, int y, int width, int height, std::string windowName, LONG style);
	virtual void Add(UiElement& component) override;
	~Window() override;

    void NotifyOnMouseHover(EventMouseStateInfo e) override;

    void NotifyOnMouseUp(EventMouseStateInfo e) override;

    void SetRenderingProvider(RenderingProvider& provider);
    RenderingProvider* GetRenderingProvider();
    void SetRenderingProvider(std::shared_ptr<RenderingProvider> renderingProvider);
    void WaitForSync();
    void Add(Element3d* element);
    Scene& Get3dScene();
};

