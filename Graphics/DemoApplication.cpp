#include "DemoApplication.h"
#include <codecvt>

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
#include "FileBrowser.h"
#include "ComboSelection.h"
#include "ComboBox.h"
#include "ComboElement.h"
#include "ListBox.h"

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

class FileBrowserTester : public MouseStateSubscriber
{
private:
	FileBrowser browser;
	TextInput& outputField;
	void ReadFile()
	{
		browser.Open(); //Lock
		std::wfstream* fileStream = browser.GetFileStream(std::ios::in);
		if (fileStream == nullptr)
			return;
		std::wstring output;
		while (!fileStream->eof())
		{
			wchar_t line[100];
			fileStream->getline(line, 100);
			output += line + wstring(L"\r\n");
		}

		outputField.SetText(output);
	}

	void SaveToFile()
	{
		browser.Save();
		std::wfstream* fileStream = browser.GetFileStream(std::ios::out);
		if (fileStream == nullptr)
			return;
		outputField.GetText();
		fileStream->write(outputField.GetText().c_str(), outputField.GetText().size());
		fileStream->close();
		delete fileStream;
	}
public:
	FileBrowserTester(TextInput& outputField) : outputField(outputField)
	{
		browser.SetTitle("Test file browser");
		browser.AddFilter("TextFiles (*.txt)", "*.txt");
		browser.AddFilter("All Files (*)", "*.*");
		browser.AddFilter("Dat files (*.dat)", "*.dat");
	}

	virtual void OnMouseDown(EventMouseStateInfo e) override
	{
	}
	virtual void OnMouseUp(EventMouseStateInfo e) override
	{
		Button* src = dynamic_cast<Button*>(e.GetSrc());

		if (src->GetText().compare(L"Browse") == 0)
			ReadFile();

		if ((src->GetText().compare(L"Save")) == 0)
			SaveToFile();

		if ((src->GetText().compare(L"Clear")) == 0)
			outputField.SetText(L"");
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


class ComboBoxTester : public ComboBoxStateSubscriber
{
private:
	ComboBox& testedComboBox;

public:
	ComboBoxTester(ComboBox& comboBox) : testedComboBox(comboBox)
	{

	}
	// Inherited via ComboBoxStateSubscriber
	virtual void OnComboBoxOpened(EventComboBoxStateInfo e) override
	{
		ComboBox& comboBox = dynamic_cast<ComboBox&>(e.GetSrc());
		CoreWindowFrame::ConsoleWrite(comboBox.GetComponentName() + "Has changed state to opened");
	}

	virtual void OnComboBoxClosed(EventComboBoxStateInfo e) override
	{
		ComboBox& comboBox = dynamic_cast<ComboBox&>(e.GetSrc());
		CoreWindowFrame::ConsoleWrite(comboBox.GetComponentName() + "Has changed state to closed");
	}

	virtual void OnSelectionChanged(EventComboBoxStateInfo e) override
	{
		ComboBox& comboBox = dynamic_cast<ComboBox&>(e.GetSrc());
		if (e.GetElement() == nullptr)
			return;
		ComboElement& element = *e.GetElement();
		CoreWindowFrame::UnicodeConsoleWrite(L"Selection changed to: " + element.GetText() + L" With value: " + to_wstring(std::any_cast<int>(element.GetValue())));
		CoreWindowFrame::UnicodeConsoleWrite(L"Curret selection: " + testedComboBox.GetSelectedElement().GetText());
	}

};

/*
* TODO
* 1) Add OnActionEvent for buttons
* 2) Repaint not being used on pure renderable components. Investigate better design --- interface pollution
*	A) Repaint should notify the parent component which in return should send a repaint request
* 3) Create a global event class that has event src as parameter. All events MUST derive from that
* 9) Input is propagated by the root to whoever has the focus. To make the design consistent, each component should propagate the input to its subcomponents. The component recieving
*	 The event should then decide whether it should notify the subscribers or not (Based on IsFocus). Revisit this design and improve.
* 10) Every renderable should have scaling option and offset option. Either relative or relative with %
* 11) Make graphical element properties consistent
* 12) Renderables lack visibility option.
* 13) Renderables should have rendering order
* 14) Checkbox should be a graphical component on its own, similar to radio button
* 15) Matrix transformation reset applies to renderables on the same layer. Graphics is a POINTER!!!!! -- I think I fixed this??? lol
* 17) Behaviors should have setters and getters. They are strategy pattern and they should be run time hot swapable
* 18) Specialize the trackbar behavior to either vertical or horizontal
* 19) If parent component has focus and hovering over sub component, the parent doesn't recieve hover -- Should differentiate between OnHover and OnMove (One hovers when mouse within, the other when focused)
* 20) Fix InternalOffset calls causing massive slow down (Internal offset calls Element offset which causes updates, this is temporarily disabled for the sake of functionality)
*		Should be removed entirely. The offsets should be handled by the matrix you fucking moron
* 21) Duplicate methods. "Listener methods" leftover in the components.
* 22) Wrap grid into a builder. The parameters should not be changed after the grid is created. Explore other options making it possible.
* 23) Finish collision checking so invalid spans can't be added to the grid --- done, grid should only call the method now.
* 24) Fix event GetSrc generics. Some return components some return any and some return your custom made generic type. Explore if it is necessary and try to avoid it.
*
* Optimization
* 1) Create rendering queve and rendering request class which specifies the rendering source. Each class should have an ID (Either real or pregenerated from the type)
*	 The rendering queve should be handled by the root and it should limit the maximum amount of renders to 30 repaints per second
* 2) Combobox memory leaks
*
* Design
* 1) Remove generics from all the events and send the src as subject by default. The inheritance hierarchy will allow you to cast it to the correct type. Src is ALWAYS a subject.
* 2) All the behaviors should be covered by a common interface to be able to make them hot swappable. (It is not going to be completely possible, but at least create a common interface for the same behavioral groups)
* 3) Trackbar
*		1) UpdateTracker() vs UpdateTrackerHeight, rename and recheck the design. What is the difference, why is UpdateTrackbar not calling UpdateTracker --- optimize and change
* 3) ListBox and combobox
*		1) Both have internal factories that generate the elements. Give an option to place any factory inside the components so any element can be part of it.
* 4) Introduce a merge function, so composite components handle events as a single logical component
*
* Bugs
* Trackbar
*	1) If trackbar width is called after trackbar control, the width doesn't get updated
*	2) If component is added to the controlled trackbar before the trackbar is added as a control, the size doesn't update
*/

void DemoApplication::LaunchDemoApp()
{
	/*ComboSelection selections = ComboSelection();
	selections.CreateComboElement(L"First");
	selections.CreateComboElement(L"Second");
	selections.CreateComboElement(L"Third");
	selections.CreateGui(100, 100, 100, 100);*/






	int width = 60;
	int height = 60;
	int offset = 100;
	int gap = 1;

	
	TestClass inputTest = TestClass();
	CheckboxTester checkboxTester = CheckboxTester();
	RadioButtonTester radioButtonTester = RadioButtonTester();

	TrackBar trackbar = TrackBar(0, 10, 10, 0, "trackbar");
	Panel panel = Panel(50, 300, 300, 250, "panel");
	panel.Add(trackbar);
	trackbar.Control(panel);


	/*
	* Listbox test start
	*/

	ListBox listBox = ListBox(225, 30, 100, 250, "TestListbox");
	ListBox listBoxDragTest = ListBox(335, 30, 100, 250, "TestListboxDrag");
	listBoxDragTest.CreateListElement(L"value 1", std::make_any<int>(1));

	for (int i = 0; i < 10; i++)
		listBox.CreateListElement(L"Value " + to_wstring(i), std::make_any<int>(i));

	/*
	* Listbox test end
	*/

	/*
	* ComboBox test start
	*/

	ComboBox comboBox = ComboBox(490, 20, 100, 30, "ComboBox");
	comboBox.SetText(L"Combo Box");
	comboBox.CreateComboElement(L"First", std::make_any<int>(1));
	comboBox.CreateComboElement(L"Second", std::make_any<int>(2));
	comboBox.CreateComboElement(L"Third", std::make_any<int>(3));
	comboBox.CreateComboElement(L"Fourth", std::make_any<int>(4));
	comboBox.CreateComboElement(L"Fifth", std::make_any<int>(5));
	ComboBoxTester comboBoxTester = ComboBoxTester(comboBox);
	comboBox.AddComboBoxStateSubscriber(comboBoxTester);

	/*
	* ComboBox test end
	*/


	/*
	* Grid Test Start
	*/
	Grid mainTestGrid = Grid(800, 10, 500, 500);
	mainTestGrid.SetGridColumns({ 100, 400 });
	mainTestGrid.SetGridRows({ 100, 300, 100 });
	mainTestGrid.SetColumnGap(2);
	mainTestGrid.SetRowGap(2);
	mainTestGrid.AddRowSpan(0, 2);

	Grid contentGrid = Grid(0, 0, 0, 0);
	contentGrid.SetRowGap(2);
	contentGrid.SetGridColumns({ 100, 100, 100, 100 });
	contentGrid.SetDefaultRowSize(100);


	Label header = Label(0, 0, 0, 0, "header");
	header.SetText(L"header");

	Label footer = Label(0, 0, 0, 0, "footer");
	footer.SetText(L"footer");

	Label content = Label(0, 0, 0, 0, "content");
	content.SetText(L"content");

	Label navBar = Label(0, 0, 0, 0, "navBar");
	navBar.SetText(L"navBar");


	mainTestGrid.Add(navBar);
	mainTestGrid.Add(header);
	mainTestGrid.Add(contentGrid);
	mainTestGrid.Add(footer);
	contentGrid.Add(content);

	for (int i = 0; i < 11; i++)
	{
		Label* contentLabel = new Label(0, 0, 100, 100, "ContentLabel" + to_string(i));
		contentGrid.Add(*contentLabel);
	}


	/*
	* File browser test start
	*/
	Button fileBrowseButton = Button(490, 320, 100, 25);
	Button fileSaveButton = Button(595, 320, 100, 25);
	Button clearButton = Button(700, 320, 100, 25);
	TextInput fileOutput = TextInput(490, 350, 300, 100, "File Content");
	fileOutput.SetMultiline(true);
	fileBrowseButton.SetText(L"Browse");
	fileSaveButton.SetText(L"Save");
	clearButton.SetText(L"Clear");
	FileBrowserTester tester = FileBrowserTester(fileOutput);
	fileSaveButton.AddMouseStateSubscriber(tester);
	clearButton.AddMouseStateSubscriber(tester);
	fileBrowseButton.AddMouseStateSubscriber(tester);

	/*
	* File browser test end
	*/

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
		Label* scrollBarTest = new Label(0, 10 + 110 * i, 100, 100, "testLabel");

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
	frame.Add(mainTestGrid);
	frame.Add(fileBrowseButton);
	frame.Add(fileOutput);
	frame.Add(fileSaveButton);
	frame.Add(clearButton);
	frame.Add(comboBox);
	frame.Add(listBox);
	frame.Add(listBoxDragTest);



	Grid calculatorGrid = Grid(10, 10, 208, 208);
	calculatorGrid.SetGridColumns({ 50, 50, 50, 50 });
	calculatorGrid.SetGridRows({ 50, 50, 50, 50 });
	calculatorGrid.AddColumnSpan(0, 3);
	calculatorGrid.SetColumnGap(2);
	calculatorGrid.SetRowGap(2);
	frame.Add(calculatorGrid);

	Label outputLabel = Label(offset, offset - height - gap, width * 3 + gap * 3, height, "outputLabel");
	Button addButton = Button(width * 3 + offset + gap * 3, offset, width + gap * 3, (height * 3 + gap * 3) / 2);
	Button multButton = Button(width * 3 + offset + gap * 3, addButton.GetY() + addButton.GetHeight(), width + gap * 3, (height * 3 + gap * 3) / 2);
	calculatorGrid.Add(outputLabel);

	multButton.SetText(L"Multiply");
	multButton.AddKeyStateSubscriber(inputTest);

	addButton.SetText(L"Add");
	SimpleCalculator calculator = SimpleCalculator(outputLabel);
	addButton.AddMouseStateSubscriber(calculator);
	multButton.AddMouseStateSubscriber(calculator);

	for (int i = 0; i < 11; i++)
	{
		Button* inputButton = new Button(0, 0, 0, 0);
		inputButton->SetText(to_wstring(i));
		if (i == 3)
			inputButton->SetText(L"Add");
		if (i == 7)
			inputButton->SetText(L"Multiply");
		calculatorGrid.Add(*inputButton);
		inputButton->AddMouseStateSubscriber(calculator);
	}
	ApplicationController::JoinThreads();
}
