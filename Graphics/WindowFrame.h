#pragma once
#include <Windows.h>
#include <condition_variable>
#include <string>
#include "Component.h"
#include <vector>
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"

using namespace std;
class CoreWindowFrame;
class WindowFrame : public Component
{
private:
	CoreWindowFrame* coreFrame;
	static condition_variable initWait;
	static bool initNotified;
	void CreateCoreWindow(int x, int y, int width, int height, string windowName);
public:
	void SetSize(int width, int height) override;
	void SetSize(Size size) override;

	void SetPosition(int x, int y) override;
	void SetPosition(Point point) override;

	void UpdateWindow();

	void Paint(Graphics& g) override;
	WindowFrame(std::string windowName);
	WindowFrame(int x, int y, int width, int height, std::string windowName);
	virtual void Add(Component& component) override;
	~WindowFrame();
};

