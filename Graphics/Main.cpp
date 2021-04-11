﻿#include "WindowFrame.h" // Needed
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
#include "EventKeyStateInfo.h"
#include "TextInput.h"
#include "CheckboxStateSubscriber.h"
#include "Checkbox.h"
#include "EventCheckboxStateInfo.h"
#include "RadioButton.h"
#include "RadioButtonStateSubscriber.h"
#include "EventRadioButtonStateInfo.h"
#include "PasswordField.h"
#include "TrackBar.h"
#include "OnAddSubscriber.h"
#include "Panel.h"
#include "Grid.h"

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

class TestClass : public KeyStateSubscriber
{
	// Inherited via KeyStateSubscriber
	virtual void OnKeyDown(EventKeyStateInfo e) override
	{

		if (e.GetInputManager().IsKeyDown(InputManager::VirtualKeys::F) && e.GetInputManager().IsKeyDown(InputManager::VirtualKeys::E))
			CoreWindowFrame::UnicodeConsoleWrite(L"OnKeyDown: F + E ");

	}
	virtual void OnKeyUp(EventKeyStateInfo e) override
	{
		CoreWindowFrame::UnicodeConsoleWrite(L"OnKeyUp +: " + std::wstring(1, e.GetUnicodeKey()));
	}
	virtual void OnKeyPressed(EventKeyStateInfo e) override
	{
		CoreWindowFrame::UnicodeConsoleWrite(L"OnKeyPressed +: " + std::wstring(1, e.GetUnicodeKey()));
	}
};

class CheckboxTester : public CheckboxStateSubscriber
{
	// Inherited via CheckboxStateSubscriber
	virtual void OnChecked(EventCheckboxStateInfo e) override
	{
		Checkbox* src = std::any_cast<Checkbox*>(e.GetSrc());
		if (e.GetState())
			CoreWindowFrame::ConsoleWrite("Checkbox: " + src->GetComponentName() + " checked!");
		else
			CoreWindowFrame::ConsoleWrite("Checkbox: " + src->GetComponentName() + " unchecked!");
	}
};

class RadioButtonTester : public RadioButtonStateSubscriber
{
	// Inherited via RadioButtonStateSubscriber
	virtual void OnRadioButtonSelected(EventRadioButtonStateInfo e) override
	{
		RadioButton* src = std::any_cast<RadioButton*>(e.GetSrc());
		if (e.IsSelected())
			CoreWindowFrame::ConsoleWrite("RadioButton: " + src->GetComponentName() + " checked!");
		else
			CoreWindowFrame::ConsoleWrite("RadioButton: " + src->GetComponentName() + " unchecked!");
	}
};

class FormSubmiter : public MouseStateSubscriber
{
private:
	Label& result;
	PasswordField& field;
public:
	FormSubmiter(Label& resultLabel, PasswordField& srcField) : result(resultLabel), field(srcField)
	{

	}


	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override
	{
	}

	virtual void OnMouseUp(EventMouseStateInfo e) override
	{
		result.SetText(field.GetText());
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


/*
* TODO
* 1) Add OnActionEvent for buttons
* 2) Repaint not being used on pure renderable components. Investigate better design --- interface pollution
*	A) Repaint should notify the parent component which in return should send a repaint request
* 3) Create a global event class that has event src as parameter. All events MUST derive from that
* 4) Create top level inheritance hierarchy class that all classes within the framework need to derive from
* 6) Checkbox - DONE
* 7) ComboBox
* 8) RadioButton - DONE
* 9) Input is propagated by the root to whoever has the focus. To make the design consistent, each component should propagate the input to its subcomponents. The component recieving
*	 The event should then decide whether it should notify the subscribers or not (Based on IsFocus). Revisit this design and improve.
* 10) Every renderable should have scaling option and offset option. Either relative or relative with %
* 11) Make graphical element properties consistent
* 12) Renderables lack visibility option.
* 13) Renderables should have rendering order
* 14) Checkbox should be a graphical component on its own, similar to radio button
* 15) Matrix transformation reset applies to renderables on the same layer. Graphic is a POINTER!!!!!
* 16) Scaling type should be somehow transfered into the matrix so the user doesn't have to calculate it on his own.
* 17) Behaviors should have setters and getters. They are strategy pattern and they should be run time hot swapable
* 18) Specialize the trackbar behavior to either vertical or horizontal
* 19) If parent component has focus and hovering over sub component, the parent doesn't recieve hover
* 20) Fix InternalOffset calls causing massive slow down (Internal offset calls Element offset which causes updates, this is temporarily disabled for the sake of functionality)
* 21) Remove methods called Listeners instead of Subscribers from component
* 
* Optimization
* 1) Create rendering queve and rendering request class which specifies the rendering source. Each class should have an ID (Either real or pregenerated from the type)
*	 The rendering queve should be handled by the root and it should limit the maximum amount of renders to 30 repaints per second
*	 The rendering queve should automatically 
*/
	
int WinEntry()
{
	int width = 60;
	int height = 60;
	int offset = 100;
	int gap = 1;


	SimpleBorder border = SimpleBorder();
	TestClass inputTest = TestClass();
	CheckboxTester checkboxTester = CheckboxTester();
	RadioButtonTester radioButtonTester = RadioButtonTester();
	TrackBar trackbar = TrackBar(0, 10, 10, 150, "trackbar");
	Panel panel = Panel(50, 300, 300, 250, "panel");
	panel.Add(trackbar);
	trackbar.Control(panel);




	/*
	* Grid Test Start
	*/
	Grid grid = Grid(800, 10, 500, 500);
	grid.SetGridColumns({ 50, 150, 75, 50 });
	grid.SetGridRows({ 100, 25, 25, 200 });

	for (int i = 0; i < 30; i++)
	{
		Label* gridTestLabel = new Label(0, 0, 0, 0, "Label");
		grid.Add(*gridTestLabel);
	}

	/*
	* Grid Test end
	*/
	

	/*
	* Password Form START
	*/
	PasswordField passwordField = PasswordField(490, 210, 100, 30, "PasswordField");
	Button submitButton = Button(600, 210, 100, 30);
	submitButton.SetText(L"Submit");
	Label resultLabel = Label(490, 250, 100, 50, "resultLabel");


	FormSubmiter submiter = FormSubmiter(resultLabel, passwordField);
	submitButton.AddMouseStateSubscriber(submiter);
	/*
	* Password Form END
	*/

	/*
	* SCROLLBAR TEST START
	*/

	for (int i = 0; i < 10; i++)
	{
		Label* scrollBarTest = new Label(0, 10+110 * i, 100, 100, "testLabel");
		
		scrollBarTest->SetText(L"TestLabel " + to_wstring(i));
		panel.Add(*scrollBarTest);
	}

	/*
	* SCROLL BAR TEST END
	*/

	RadioButton radioButton1 = RadioButton(600, 100, 100, 30, "radioButton1");
	RadioButton radioButton2 = RadioButton(600, 135, 100, 30, "radioButton2");
	RadioButton radioButton3 = RadioButton(600, 170, 100, 30, "radioButton3");

	RadioButton radioButtonG1 = RadioButton(490, 100, 100, 30, "radioButtonG1");
	RadioButton radioButtonG2 = RadioButton(490, 135, 100, 30, "radioButtonG2");
	RadioButton radioButtonG3 = RadioButton(490, 170, 100, 30, "radioButtonG3");

	radioButton1.AddRadioButtonStateSubscriber(radioButtonTester);
	radioButton2.AddRadioButtonStateSubscriber(radioButtonTester);
	radioButton3.AddRadioButtonStateSubscriber(radioButtonTester);

	radioButtonG1.AddRadioButtonStateSubscriber(radioButtonTester);
	radioButtonG2.AddRadioButtonStateSubscriber(radioButtonTester);
	radioButtonG3.AddRadioButtonStateSubscriber(radioButtonTester);

	Label groupLabel1 = Label(600, 60, 100, 30, "Group1");
	groupLabel1.SetText(L"Group 1 buttons");
	Label groupLabel2 = Label(490, 60, 100, 30, "Group2");
	groupLabel2.SetText(L"Group 2 buttons");

	radioButton1.SetText(L"First");
	radioButton2.SetText(L"Second");
	radioButton3.SetText(L"Third");

	radioButtonG1.SetText(L"First");
	radioButtonG2.SetText(L"Second");
	radioButtonG3.SetText(L"Third");

	radioButton1.AddToGroup(radioButton2);
	radioButton2.AddToGroup(radioButton3);

	radioButtonG1.AddToGroup(radioButtonG2);
	radioButtonG2.AddToGroup(radioButtonG3);


	TextInput input = TextInput(500, 500, 200, 100, "input");
	input.SetText(L"おはよお");

	Checkbox checkbox = Checkbox(600, 20, 105, 35, "Checkbox1");
	checkbox.SetText(L"Test checkbox");
	checkbox.AddCheckboxStateSubscriber(checkboxTester);

	input.SetMultiline(true);

	WindowFrame frame = WindowFrame(800, 600, 800, 600, "testFrame");
	frame.Add(input);
	frame.Add(checkbox);

	frame.Add(radioButton1);
	frame.Add(radioButton2);
	frame.Add(radioButton3);

	frame.Add(radioButtonG1);
	frame.Add(radioButtonG2);
	frame.Add(radioButtonG3);
	frame.Add(groupLabel1);
	frame.Add(groupLabel2);
	frame.Add(passwordField);
	frame.Add(resultLabel);
	frame.Add(submitButton);
	frame.Add(panel);
	frame.Add(grid);

	Label outputLabel = Label(offset, offset - height - gap, width*3 + gap*3, height, "outputLabel");
	Button addButton = Button(width * 3 + offset + gap*3, offset, width + gap*3, (height * 3 + gap*3)/2);
	Button multButton = Button(width * 3 + offset + gap * 3, addButton.GetY() + addButton.GetHeight(), width + gap * 3, (height * 3 + gap * 3)/2);
	addButton.SetProperty("background-color", Gdiplus::Color::Red);

	multButton.SetText(L"Multiply");
	multButton.AddKeyStateSubscriber(inputTest);
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