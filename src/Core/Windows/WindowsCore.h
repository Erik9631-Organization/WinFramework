#pragma once
#include "Window.h"
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "Utils/ApplicationController.h"
#include "Events/ResizeSubscriber.h"
#include "Events/MoveSubscriber.h"
#include "api/Movable.h"
#include "api/Resizable.h"
#include "EventTypes/EventMoveInfo.h"
#include "TimerSubscriber.h"
#include "Timer.h"
#include "EntryStateSubscriber.h"
#include "RenderEventInfo.h"
#include <functional>
#include "CoreMediator.h"
#include "CoreSubject.h"
#include "Core.h"

using namespace Gdiplus;
class RenderingProvider;
/**
 * The core frame, the raw root of the entire system. The class is wrapped by Window class.
 * This class is responsible for handling the windows messaging, creating events and responsible for the rendering system.
 */
class WindowsCore : public RenderCommander, public Core
{


private:
    class MsgSubject : ResizeSubject
    {
    public:
        void NotifyOnResizeSubscribers(EventResizeInfo event) override;
        void AddOnResizeSubscriber(ResizeSubscriber &subscriber) override;
        void RemoveOnResizeSubscriber(ResizeSubscriber &subscriber) override;
    private:
        vector<reference_wrapper<ResizeSubscriber>> resizeSubscribers;
    };
    vector<CoreSubscriber*> coreSubscribers;
    MsgSubject preProcessSubject;
    CoreMediator coreAdapter;
	HWND windowHandle;
	void CreateConsole();
	Window* wrapperFrame = nullptr;
	void ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam);
    DefaultRender renderBehavior;
	HINSTANCE hInstance;
    std::thread* updateThread;
    std::string windowName;
    LONG style;

	Vector2 mousePos;
	Vector2 prevMousePos;
	Vector2 mouseDelta;
	Vector2 relativePos;
    Vector2 lockCursorSize;
    RECT lockCursorRegion;
    bool cursorLocked = false;
	RenderingProvider* renderingProvider = nullptr;
	bool updateFinished = true;
	std::condition_variable updateFinishedSignal;
	int targetFps = 60;
	Timer fpsTimer;
	bool eventBased = false;
    mutex updateMutex;
    bool processMessages = true;
    void UpdateGlobalInputState();
    void UpdateLockCursor();
    void CreateWinApiWindow();
    WindowsCore(Window *wrapperFrame, const string &windowName, LONG style);
public:
    void SetLockCursorSize(const Vector2& size);
    void LockCursor(const bool& lockState);
    const bool& IsCursorLocked() const;
    bool IsEventBased() const;
    void SetEventBased(bool eventBased);
//    std::unique_ptr<WindowsCore> static Create(Window *wrapperFrame, const string &windowName, LONG style);
	/**
	 * Updates the scale of the window
	 */
	void UpdateScale();
	/**
	 * Constructor
	 * \param args reference to LiiEntry arguments
	 * \param wrapperFrame reference to the frame that wrapps the core frame
	 * \param windowName the name of the window which is being displayed
	 * \param style the style of the window that should be used. Please check MSDN for window styles.
	 */

	/**
	 * The message loop of the window. This is where all the messages are processed.
	 */
    void WindowsMessageLoop();
	/**
	 * Called by CoreWindow::WindowsMessageLoop to process a specific message.
	 */
	void ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	/**
	 * Repaints the current window.
	 */
	void Redraw();
	/**
	 * Closes the current window.
	 */
	void Close();
	/**
	 * Gets the wrapper frame of this class.
	 */
    Window * GetWrapperFrame();
	/**
	 * Gets the hardware context of the current window.
	 */
	HDC* GetHdc();
	/**
	 * Gets the handle to the current window
	 */
	HWND GetWindowHandle();
	/**
	 * Output to console
	 * /param output text to output.
	 */
	static void ConsoleWrite(string output);
	/**
	 * Output to console as unicode.
	 * /param output unicode text to output.
	 */
	static void UnicodeConsoleWrite(std::wstring output);
	~WindowsCore();

	// Inherited via Renderable
	/**
	 * OnRenderSync event
	 * \param e event object to pass.
	 */
	virtual void OnRenderSync(RenderEventInfo e) override;
	
	/**
	 * Similar to Redraw, but also updates the position and scale.
	 * \param e event object to pass.
	 */
	virtual void Repaint() override;
	/**
	 * Adds new renderable to the system which will be painted on the canvas.
	 * \param renderable the renderable object reference to pass
	 */
	virtual void AddRenderCommander(RenderCommander &renderable) override;
	/**
	 * Removes an existing renderable by reference.
	 * \param reference of the renderable to remove.
	 */
	virtual void RemoveRenderCommander(RenderCommander& renderable) override;
	/**
	 * Returns the list of renderables.
	 * \return a vector of references to the renderables in the current system,
	 */
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
	/**
	 * Changes attributes of the window. Some of these attributes are not changable at runtime. Refer to MSDN.
	 * \param index the index of the attribute to change
	 * \param parameter the flag of the attribute to set it to
	 * \return returns non negative value on fail and 0 on success.
	 */
    long long int SetAttributes(int index, long long int parameter);

	/**
	 * Removes attributes of the window. Some of these attributes are not changable at runtime. Refer to MSDN.
	 * \param index the index of the attribute to change
	 * \param parameter the flag of the attribute to remove.
	 * \return returns non negative value on fail and 0 on success.
	 */


	void AddOnResizePreProcessSubsriber(ResizeSubscriber& subscriber);
	void RemoveOnResizePreProcessSubsriber(ResizeSubscriber& subscriber);
	void SetRenderingProvider(RenderingProvider& provider);
	RenderingProvider* GetRenderingProvider();
    void OnSync(const DrawData &data) override;
    void WaitForUpdateToFinish();
    void NotifyCoreOnDestroy(std::any src) override;
    void NotifyCoreOnClose(std::any src) override;
    void NotifyCoreOnMove(EventMoveInfo e) override;
    void NotifyCoreOnResize(EventResizeInfo e) override;
    void NotifyCoreOnMouseMove(EventMouseStateInfo e) override;
    void NotifyCoreOnMouseLButtonDown(EventMouseStateInfo e) override;
    void NotifyCoreOnMouseLButtonUp(EventMouseStateInfo e) override;
    void NotifyCoreOnKeyUp(EventKeyStateInfo e) override;
    void NotifyCoreOnKeyDown(EventKeyStateInfo e) override;
    void NotifyCoreOnWheelMoved(EventKeyStateInfo e) override;
    void AddCoreSubscriber(CoreSubscriber *subscriber) override;
    void RemoveCoreSubscriber(CoreSubscriber *subscriber) override;
    void NotifyCoreOnMousePressed(EventMouseStateInfo e) override;
    void NotifyCoreOnKeyPressed(EventKeyStateInfo e) override;

    long long int RemoveAttribute(int index, long long int parameter) override;

    void Start() override;

    static unique_ptr<Core> Create(Window *window, std::any args);

    void SetWindow(Window *window) override;
};
