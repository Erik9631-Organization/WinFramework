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
	void assignGraphicsToNodes(MultiTree<Component&>& node, Rect viewPort);
	void NotifyMouseState(Gdiplus::Point point);

	DefaultRender renderBehavior;

public:
	CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame,string windowName);
	void MessageLoop();
	void ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	void RedrawWindow();
	WindowFrame& GetWrapperFrame();
	HDC* GetHdc();
	HWND GetWindowHandle();
	static void ConsoleWrite(string output);
	~CoreWindowFrame();

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

