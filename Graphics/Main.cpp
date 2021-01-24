#include "WindowFrame.h" // Needed
#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include "Button.h"
#include "Pane.h"
#include <Windows.h>

#include <string>
#include "CoreWindowFrame.h"
#include <gdiplus.h>
#include "DefaultMultiTree.h"

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
	WindowFrame frame = WindowFrame("testFrame");
	Button button1 = Button(0, 0, 10, 10);
	button1.SetComponentName("button1");

	Button button2 = Button(0, 0, 10, 10);
	button2.SetComponentName("button2");

	Button button3 = Button(0, 0, 10, 10);
	button3.SetComponentName("button3");

	Button button4 = Button(0, 0, 10, 10);
	button4.SetComponentName("button4");

	//frame.Add(button1);
	button1.Add(button2);
	button1.Add(button3);
	button3.Add(button4);

	CoreWindowFrame::ConsoleWrite(button4.GetParent()->GetParent()->GetComponentNode().Get(0).GetValue().GetComponentName());

	system("PAUSE"); // Replace with Join
	return 0;
} 