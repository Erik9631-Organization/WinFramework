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
	CoreWindowFrame* coreFrame;
	thread* windowThread;
	condition_variable* initWait;
	bool initNotified = false;
	Background background;

	void CreateCoreWindow();

public:
	void SetSize(int width, int height) override;
	void SetSize(Size size) override;
	void Repaint() override;;

	void SetPosition(int x, int y) override;
	void SetPosition(Point point) override;

	void UpdateWindow();
	WindowFrame(std::string windowName);
	WindowFrame(int x, int y, int width, int height, std::string windowName);
	virtual void Add(Component& component) override;
	~WindowFrame();
};

