#pragma once
#include "WindowFrame.h"
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "OnAddListener.h"
#include "ApplicationController.h"
#include "ResizeSubscriber.h"
#include "MoveSubscriber.h"
#include "Movable.h"
#include "Resizable.h"
#include "EventMoveInfo.h"


using namespace std;
using namespace Gdiplus;
class CoreWindowFrame : public Resizable, Movable
{
private:
	vector<reference_wrapper<MoveSubscriber>> moveSubscribers;
	vector<reference_wrapper<ResizeSubscriber>> resizeSubscribers;
	HWND windowHandle;
	Gdiplus::Size size;
	Gdiplus::Point position;
	void CreateConsole();
	HDC secondaryBuffer;
	WindowFrame& wrapperFrame;
	HDC CreateGraphicsBuffer();
	void CleanGraphicsBuffer();
	void RenderGraphics(HDC GraphicsBuffer);
	void AssignGraphicsToComponents();
	vector<reference_wrapper<Component>> components;

public:
	CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame,string windowName);
	void ComponentAdded(Component& component);
	void MessageLoop();
	void ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	void RedrawWindow();
	WindowFrame& GetWrapperFrame();
	HDC* GetHdc();
	int GetX();
	int GetY();
	HWND GetWindowHandle();
	static void ConsoleWrite(string output);
	~CoreWindowFrame();

	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual Gdiplus::Size GetSize() override;
	virtual int GetWidth() override;
	virtual int GetHeight() override;
	virtual void SetSize(Gdiplus::Size size) override;
	virtual void SetWidth(int width) override;
	virtual void SetHeight(int height) override;

	// Inherited via Movable
	virtual Gdiplus::Point GetPosition() override;
	virtual void SetPosition(Gdiplus::Point position) override;
	virtual void SetX(int x) override;
	virtual void SetY(int y) override;

	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;

	// Inherited via Movable
	virtual void SetPosition(int x, int y) override;

	// Inherited via Resizable
	virtual void SetSize(int width, int height) override;
};

