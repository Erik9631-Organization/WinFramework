#pragma once
#include <Windows.h>
#include <condition_variable>
#include <string>
#include "Components/Component.h"
#include <vector>
#include "Events/MoveSubscriber.h"
#include "Events/ResizeSubscriber.h"
#include "Graphics/Background.h"

using namespace std;
class CoreWindowFrame;

/**
 * This class wraps the CoreWindowFrame class and is responsible for delegating most of the method calls to that class.
 * It is also the top root of the containment hierarchy and is the first component that should be created in your application.
 * All the components that are to be displayed within the window should be added via the Component::Add function which this class inherits.
 */
class WindowFrame : public Component
{
private:
	Component* currentFocus = nullptr;
	Component* currentCapture = nullptr;

	CoreWindowFrame* coreFrame = nullptr;
	thread* windowThread = nullptr;
	condition_variable* initWait = nullptr;
	bool initNotified = false;
	Background background;

	void CreateCoreWindow(LONG style);

public:
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

	void SetSize(int width, int height) override;
	void SetSize(Size size) override;
	void Repaint() override;
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;

	void SetPosition(int x, int y) override;
	void SetPosition(Point point) override;

	virtual void NotifyOnKeyDown(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) override;
	void CloseWindow();

	void UpdateWindow();
	WindowFrame(std::string windowName);
	WindowFrame(int x, int y, int width, int height, std::string windowName);
	WindowFrame(int x, int y, int width, int height, std::string windowName, LONG style);
	virtual void Add(Component& component) override;
	~WindowFrame();

    void NotifyOnMouseHover(EventMouseStateInfo e) override;

    void NotifyOnMouseUp(EventMouseStateInfo e) override;
};

