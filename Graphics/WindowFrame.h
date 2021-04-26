#pragma once
#include <Windows.h>
#include <condition_variable>
#include <string>
#include "Component.h"
#include <vector>
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "Background.h"

using namespace std;
class CoreWindowFrame;


class WindowFrame : public Component
{
private:
	Component* currentFocus = nullptr;
	CoreWindowFrame* coreFrame;
	thread* windowThread;
	condition_variable* initWait;
	bool initNotified = false;
	Background background;

	void CreateCoreWindow();

public:
	void AddWindowStyle(LONG styleFlags);
	void RemoveWindowStyle(LONG styleFlags);

	void AddWindowExtendedStyle(LONG styleFlags);
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

	void UpdateWindow();
	WindowFrame(std::string windowName);
	WindowFrame(int x, int y, int width, int height, std::string windowName);
	virtual void Add(Component& component) override;
	~WindowFrame();
};

