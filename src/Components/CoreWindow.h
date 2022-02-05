#pragma once
#include "Window.h"
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "Utils/ApplicationController.h"
#include "Events/ResizeSubscriber.h"
#include "Events/MoveSubscriber.h"
#include "Movable.h"
#include "Resizable.h"
#include "EventTypes/EventMoveInfo.h"
#include "TimerSubscriber.h"
#include "Timer.h"


using namespace std;
using namespace Gdiplus;
class RenderingProvider;
/**
 * The core frame, the raw root of the entire system. The class is wrapped by Window class.
 * This class is responsible for handling the windows messaging, creating events and responsible for the rendering system.
 */
class CoreWindow : Renderable
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
    MsgSubject preProcessSubject;

	HWND windowHandle;
	void CreateConsole();
	HDC secondaryDc;
	Window& wrapperFrame;
	HBITMAP secondaryBitmap;
	void ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam);
	DefaultRender renderBehavior;
	HINSTANCE hInstance;

	Vector2 mousePos;
	Vector2 prevMousePos;
	Vector2 mouseDelta;
	Vector2 relativePos;
	RenderingProvider* renderingProvider = nullptr;
public:
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
	CoreWindow(ApplicationController::WinEntryArgs &args, Window& wrapperFrame,string windowName, LONG style);
	/**
	 * The message loop of the window. This is where all the messages are processed.
	 */
	void MessageLoop();
	/**
	 * Called by CoreWindow::MessageLoop to process a specific message.
	 */
	void ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	/**
	 * Repaints the current window.
	 */
	void RedrawWindow();
	/**
	 * Closes the current window.
	 */
	void CloseWindow();
	/**
	 * Gets the wrapper frame of this class.
	 */
	Window& GetWrapperFrame();
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
	~CoreWindow();

	// Inherited via Renderable
	/**
	 * OnRender event
	 * \param e event object to pass.
	 */
	virtual void OnRender(RenderEventInfo e) override;
	
	/**
	 * Similar to RedrawWindow, but also updates the position and scale.
	 * \param e event object to pass.
	 */
	virtual void Repaint() override;
	/**
	 * Adds new renderable to the system which will be painted on the canvas.
	 * \param renderable the renderable object reference to pass
	 */
	virtual void AddRenderable(Renderable &renderable) override;
	/**
	 * Removes an existing renderable by reference.
	 * \param reference of the renderable to remove.
	 */
	virtual void RemoveRenderable(Renderable& renderable) override;
	/**
	 * Returns the list of renderables.
	 * \return a vector of references to the renderables in the current system,
	 */
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
	/**
	 * Changes attributes of the window. Some of these attributes are not changable at runtime. Refer to MSDN.
	 * \param index the index of the attribute to change
	 * \param parameter the flag of the attribute to set it to
	 * \return returns non negative value on fail and 0 on success.
	 */
	LONG SetWindowAttributes(int index, LONG parameter);

	/**
	 * Removes attributes of the window. Some of these attributes are not changable at runtime. Refer to MSDN.
	 * \param index the index of the attribute to change
	 * \param parameter the flag of the attribute to remove.
	 * \return returns non negative value on fail and 0 on success.
	 */
	LONG RemoveWindowAttributes(int index, LONG parameter);


	void AddOnResizePreProcessSubsriber(ResizeSubscriber& subscriber);
	void RemoveOnResizePreProcessSubsriber(ResizeSubscriber& subscriber);
	void SetRenderingProvider(RenderingProvider& provider);
	RenderingProvider* GetRenderingProvider();
};

