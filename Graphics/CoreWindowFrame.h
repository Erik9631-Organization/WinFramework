#pragma once
#include "WindowFrame.h"
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "ApplicationController.h"
#include "ResizeSubscriber.h"
#include "MoveSubscriber.h"
#include "Movable.h"
#include "Resizable.h"
#include "EventMoveInfo.h"


using namespace std;
using namespace Gdiplus;
/**
 * The core frame, the raw root of the entire system. The class is wrapped by WindowFrame class.
 * This class is responsible for handling the windows messaging, creating events and responsible for the rendering system.
 */
class CoreWindowFrame : Renderable
{
private:
	int lastMouseX;
	int lastMouseY;
	HWND windowHandle;
	void CreateConsole();
	HDC secondaryBuffer;
	WindowFrame& wrapperFrame;
	HBITMAP currentBitmap;
	HDC CreateGraphicsBuffer();
	void CleanGraphicsBuffer();
	void RenderGraphics(HDC GraphicsBuffer);
	void AssignGraphicsToComponents();
	void assignGraphicsToNodes(MultiTree<Component&>& node, Region& clippingRegion);
	void NotifyMouseState(Gdiplus::Point point);
	void ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam);
	DefaultRender renderBehavior;
	HINSTANCE hInstance;

public:
	/**
	 * Updates the scale of the window
	 */
	void UpdateScale();
	/**
	 * Constructor
	 * \param args reference to WinEntry arguments
	 * \param wrapperFrame reference to the frame that wrapps the core frame
	 * \param windowName the name of the window which is being displayed
	 * \param style the style of the window that should be used. Please check MSDN for window styles.
	 */
	CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame,string windowName, LONG style);
	/**
	 * The message loop of the window. This is where all the messages are processed.
	 */
	void MessageLoop();
	/**
	 * Called by CoreWindowFrame::MessageLoop to process a specific message.
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
	WindowFrame& GetWrapperFrame();
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
	~CoreWindowFrame();

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
	virtual void AddRenderable(Renderable& renderable) override;
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
};

