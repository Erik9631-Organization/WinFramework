#include "WindowFrame.h" // Needed
#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include "Button.h"
#include "Pane.h"
#include <Windows.h>

#include <string>
#include "CoreWindowFrame.h"
#include <gdiplus.h>

//Testing
#include "AddEventInfo.h"
using namespace std;

/**
* TODO
* Create WindowManager
* Window manager is responsible for processing messages, fetching windows and its positions, finding window by ID and so on.
* ApplicationController should only take care of the entry point and the GDI startup. It should also recieve all the events in the framework and dispatch them to the appropriate event handler
*/

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return WinEntry();
}

int WinEntry()
{
	WindowFrame frame = WindowFrame("Window 1");
	frame.SetPosition(100, 100);
	Pane pane = Pane();
	pane.SetPosition(50, 50);
	pane.SetColor(0, 0, 0);
	frame.Add(pane);
	Button button2 = Button(10, 10, 20, 20);
	pane.Add(button2);


	system("PAUSE"); // Replace with Join
	return 0;
}