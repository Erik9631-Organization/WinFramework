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
#include "EventUpdateInfo.h"
#include "MouseInteractable.h"
#include "MouseStateSubscriber.h"
#include "EventMouseStateInfo.h"
#include "Label.h"
#include "SimpleBorder.h"
#include "ActivateSubscriber.h"
#include "EventOnActivateInfo.h"

using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	int returnVal = WinEntry();

	//Thread cleanup
	ApplicationController::JoinThreads();

	return returnVal;
}

class SimpleCalculator : public MouseStateSubscriber
{
	// Inherited via MouseStateSubscriber
	Label& outputLabel;
private:
	int currentValue = 0;
	int result = 0;
	void AddValues(int value)
	{
		result += value;
		currentValue = 0;
		outputLabel.SetText(L"Result: " + to_wstring(result) + L"\n");
	}

	void MultiplyValues(int value)
	{
		result *= value;
		currentValue = 0;
		outputLabel.SetText(L"Result: " + to_wstring(result) + L"\n");
	}

public:
	SimpleCalculator(Label& label) : outputLabel(label)
	{

	}
	virtual void OnMouseDown(EventMouseStateInfo e) override
	{

	}
	virtual void OnMouseUp(EventMouseStateInfo e) override
	{
		Button* button = dynamic_cast<Button*>(e.GetSrc());
		if (button->GetText().compare(L"Add") == 0)
		{
			AddValues(currentValue);
			return;
		}

		if (button->GetText().compare(L"Multiply") == 0)
		{
			MultiplyValues(currentValue);
			return;
		}
		int value = std::stoi(button->GetText());
		currentValue = (currentValue * 10) + value;
		outputLabel.SetText(outputLabel.GetText() + button->GetText());
	}
	virtual void OnMousePressed(EventMouseStateInfo e) override
	{

	}
	virtual void OnMouseMove(EventMouseStateInfo e) override
	{

	}
	virtual void OnMouseEntered(EventMouseStateInfo e) override
	{

	}
	virtual void OnMouseLeft(EventMouseStateInfo e) override
	{

	}
};

class ActivateTester : public ActivateSubscriber
{
	// Inherited via ActivateSubscriber
	virtual void OnActiveStateChanged(EventOnActivateInfo e) override
	{
		if (e.GetState() == true)
			CoreWindowFrame::ConsoleWrite("Active");
		else
			CoreWindowFrame::ConsoleWrite("Inactive");
	}
};

/*
* TODO
* 2) Add OnActionEvent for buttons
* 3) Repaint not being used on pure renderable components. Investigate better design --- interface pollution
*	A) Repaint should notify the parent component which in return should send a repaint request
* 4) Create a global event class that has event src as parameter. All events MUST derive from that
* 5) Create top level inheritance hierarchy class that all classes within the framework need to derive from
* 6) Expand renderables so no methods are required to change properties. Properties should be dynamic and they should be stringified. Can be turned into a stylesheet. - DONE
*	A) Create access tool class that takes string as an input and variadic template as arguments, these should be passed to the property pulled from the associated class - DONE
* 7) Create a class that can turn events into enumerable data.
* 8) Component focus - DONE
*/
	
int WinEntry()
{
	int width = 60;
	int height = 60;
	int offset = 100;
	int gap = 1;

	//testing
	ActivateTester tester = ActivateTester();
	//testing end

	SimpleBorder border = SimpleBorder();

	WindowFrame frame = WindowFrame(800, 600, 800, 600, "testFrame");
	frame.AddOnActivateSubscriber(tester);

	Label outputLabel = Label(offset, offset - height - gap, width*3 + gap*3, height, "outputLabel");
	Button addButton = Button(width * 3 + offset + gap*3, offset, width + gap*3, (height * 3 + gap*3)/2);
	Button multButton = Button(width * 3 + offset + gap * 3, addButton.GetY() + addButton.GetHeight(), width + gap * 3, (height * 3 + gap * 3)/2);
	multButton.AddOnActivateSubscriber(tester);
	addButton.SetProperty("background-color", Gdiplus::Color::Red);

	multButton.SetText(L"Multiply");
	frame.Add(multButton);

	addButton.SetText(L"Add");
	frame.Add(addButton);
	frame.Add(outputLabel);
	SimpleCalculator calculator = SimpleCalculator(outputLabel);
	addButton.AddMouseStateSubscriber(calculator);
	multButton.AddMouseStateSubscriber(calculator);


	Button button1 = Button(5, 5, 35, 35);
	int counter = 0;

	for (int iy = 0; iy < 3; iy++)
	{
		for (int ix = 0; ix < 3; ix++)
		{
			counter++;
			Button* inputButton = new Button(offset + (ix * (width+gap)), offset + iy * (height+gap), width, height);
			inputButton->SetText(to_wstring(counter));
			frame.Add(*inputButton);
			inputButton->AddMouseStateSubscriber(calculator);
		}

	}


	ApplicationController::JoinThreads();
	return 0;
} 