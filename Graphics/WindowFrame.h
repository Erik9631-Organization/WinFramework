#pragma once
#include <Windows.h>
#include <string>
#include "Component.h"
#include <vector>
using namespace std;

class CoreWindowFrame; 
class WindowFrame : public Component, public OnAddListener
{
private:
	CoreWindowFrame* coreFrame;
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
	~WindowFrame();

	// Inherited via OnAddListener
	virtual void OnAdd(Component & component) override;
};

