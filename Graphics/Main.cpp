#include "WindowFrame.h" // Needed
#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include "Button.h"
#include "Pane.h"
#include <Windows.h>

#include <string>
#include "CoreWindowFrame.h"
using namespace std;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return WinEntry();
}
// Addable, resizable, movable, paintable - Add all these interfaces
int WinEntry()
{
	WindowFrame* frame = new WindowFrame("Window 1");
	frame->SetPosition(100, 100);
	Button* button = new Button(0, 0, 100, 100);
	frame->Add(button);

	system("PAUSE");
	return 0;
}