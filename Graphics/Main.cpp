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

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return WinEntry();
}

int WinEntry()
{
	WindowFrame* frame = new WindowFrame("Window 1");
	frame->SetPosition(100, 100);
	Button button = Button(0, 0, 100, 100);
	frame->Add(button);
	Button button2 = Button(10, 10, 50, 50);
	button.Add(button2);


	system("PAUSE");
	return 0;
}