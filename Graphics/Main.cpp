#include "WindowFrame.h" // Needed
#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include "Button.h"
#include <Windows.h>

#include <string>
#include "CoreWindowFrame.h"
#include <gdiplus.h>
#include "DefaultMultiTree.h"
#include "MoveSubscriber.h"
#include "EventUpdateInfo.h";
using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	int returnVal = WinEntry();

	//Thread cleanup
	ApplicationController::JoinThreads();

	return returnVal;
}

class TestSubscriber : public MoveSubscriber
{
	// Inherited via MoveSubscriber
	virtual void OnMove(EventMoveInfo e) override
	{
		CoreWindowFrame::ConsoleWrite(to_string(e.GetPosition().X) + " " + to_string(e.GetPosition().Y));
	}
};
	
int WinEntry()
{
	WindowFrame frame = WindowFrame(800, 600, 800, 600, "testFrame");

	TestSubscriber subscriber = TestSubscriber();
	Button button1 = Button(100, 50, 100, 40);
	Button button2 = Button(100, 100, 80, 80);
	Button button3 = Button(0, 0, 10, 10);

	button1.SetComponentName("button1");
	button2.SetComponentName("button2");

	button3.SetComponentName("button3");
	button3.SetBackgroundColor(Gdiplus::Color::Red);
	button2.Add(button3);
	frame.Add(button1);
	frame.Add(button2);


	ApplicationController::JoinThreads();
	return 0;
} 