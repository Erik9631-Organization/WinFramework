#include "DemoApplication.h"
#include <codecvt>

#include "Window.h" // Needed
#include "Components/Button.h"

#include <string>
#include "Core/Windows/WindowsCore.h"
#include "EventTypes/EventUpdateInfo.h"
#include "Events/MouseStateSubscriber.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "Components/Label.h"
#include "EventTypes/EventOnActivateInfo.h"
#include "EventTypes/EventKeyStateInfo.h"
#include "Components/TextInput.h"
#include "Events/CheckboxStateSubscriber.h"
#include "Components/Checkbox.h"
#include "EventTypes/EventCheckboxStateInfo.h"
#include "Components/RadioButton.h"
#include "Events/RadioButtonStateSubscriber.h"
#include "EventTypes/EventRadioButtonStateInfo.h"
#include "Components/PasswordField.h"
#include "Components/Panel.h"
#include "Components/Grid/Grid.h"
#include "Components/FileBrowser.h"
#include "Components/ListBox.h"
#include "ScrollBar.h"
#include <iostream>
using namespace std;

std::unique_ptr<Window> frame;

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

    void OnMouseCaptured(EventMouseStateInfo e) override
    {

    }
};

class InputTester : public KeyStateSubscriber
{
	// Inherited via KeyStateSubscriber
	virtual void OnKeyDown(EventKeyStateInfo e) override
	{
		UiElement* src = dynamic_cast<UiElement*>(e.GetSource());
        std::cout << src->GetComponentName() << endl;

	}
	virtual void OnKeyUp(EventKeyStateInfo e) override
	{
		UiElement* src = dynamic_cast<UiElement*>(e.GetSource());
		std::cout << src->GetComponentName() << std::endl;
	}
	virtual void OnKeyPressed(EventKeyStateInfo e) override
	{
		UiElement* src = dynamic_cast<UiElement*>(e.GetSource());
        std::cout << src->GetComponentName() << std::endl;
	}
};

class CheckboxTester : public CheckboxStateSubscriber
{
	// Inherited via CheckboxStateSubscriber
	virtual void OnChecked(EventCheckboxStateInfo e) override
	{
		Checkbox* src = dynamic_cast<Checkbox*>(e.GetSrc());
		if (e.GetState())
            std::cout << "Checkbox: " << src->GetComponentName() << " checked!" << std::endl;
		else
            std::cout <<"Checkbox: " << src->GetComponentName() << " unchecked!" << std::endl;
	}
};

class RadioButtonTester : public RadioButtonStateSubscriber
{
	// Inherited via RadioButtonStateSubscriber
	virtual void OnRadioButtonSelected(EventRadioButtonStateInfo e) override
	{
		RadioButton* src = dynamic_cast<RadioButton*>(e.GetSrc());
		if (e.IsSelected())
            std::cout << "RadioButton: " + src->GetComponentName() + " checked!" << std::endl;
		else
            std::cout << "RadioButton: " + src->GetComponentName() + " unchecked!" << std::endl;
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

    void OnMouseCaptured(EventMouseStateInfo e) override
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

    void OnMouseCaptured(EventMouseStateInfo e) override
    {

    }
};


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

//
	InputTester* inputTest = new InputTester();
	CheckboxTester* checkboxTester = new CheckboxTester();
	RadioButtonTester* radioButtonTester = new RadioButtonTester();

    auto scrollbar = std::make_unique<ScrollBar>(0, 0, 10, 0, "ScrollBar");

	auto panel = std::make_unique<Panel>(50, 300, 300, 250, "panel");
    ScrollBar::Control(panel.get(), std::move(scrollbar));


	/*
	* Listbox test start
	*/

	auto listBox = std::make_unique<ListBox>(225, 30, 100, 250, "TestListbox");
	auto listBoxDragTest = std::make_unique<ListBox>(335, 30, 100, 250, "TestListboxDrag");
	listBoxDragTest->CreateListElement(L"value 1", std::make_any<int>(1));

	for (int i = 0; i < 10; i++)
		listBox->CreateListElement(L"Value " + to_wstring(i), std::make_any<int>(i));

	/*
	* Listbox test end
	*/

	/*
	* Grid Test Start
	*/
	auto mainTestGrid = std::make_unique<Grid>(800, 10, 500, 500);
	mainTestGrid->SetGridColumns({ 100, 400 });
	mainTestGrid->SetGridRows({ 100, 300, 100 });
	mainTestGrid->SetColumnGap(2);
	mainTestGrid->SetRowGap(2);
	mainTestGrid->AddRowSpan(0, 2);

	auto contentGrid = std::make_unique<Grid>(0, 0, 0, 0);
	contentGrid->SetRowGap(2);
	contentGrid->SetGridColumns({ 100, 100, 100, 100 });
	contentGrid->SetDefaultRowSize(100);


	auto header = std::make_unique<Label>(0, 0, 0, 0, "header");
	header->SetText(L"header");

	auto footer = std::make_unique<Label>(0, 0, 0, 0, "footer");
	footer->SetText(L"footer");

	auto content = std::make_unique<Label>(0, 0, 0, 0, "content");
	content->SetText(L"content");

	auto navBar = std::make_unique<Label>(0, 0, 0, 0, "navBar");
	navBar->SetText(L"navBar");


	mainTestGrid->Add(std::move(navBar));
	mainTestGrid->Add(std::move(header));
    auto& ContentGridRef = *contentGrid;
	mainTestGrid->Add(std::move(contentGrid));
	mainTestGrid->Add(std::move(footer));
    ContentGridRef.Add(std::move(content));

	for (int i = 0; i < 11; i++)
	{
		auto contentLabel = std::make_unique<Label>(0, 0, 100, 100, "ContentLabel" + to_string(i));
        ContentGridRef.Add(std::move(contentLabel));
	}


	/*
	* File browser test start
	*/
	auto fileBrowseButton = std::make_unique<Button>(490, 320, 100, 25);
	auto fileSaveButton = std::make_unique<Button>(595, 320, 100, 25);
	auto clearButton = std::make_unique<Button>(700, 320, 100, 25);
	auto fileOutput = std::make_unique<TextInput>(490, 350, 300, 100, "File Content");
	fileOutput->SetMultiline(true);
	fileBrowseButton->SetText(L"Browse");
	fileSaveButton->SetText(L"Save");
	clearButton->SetText(L"Clear");
	auto tester = new FileBrowserTester(*fileOutput);
	fileSaveButton->AddMouseStateSubscriber(*tester);
	clearButton->AddMouseStateSubscriber(*tester);
	fileBrowseButton->AddMouseStateSubscriber(*tester);

	/*
	* File browser test end
	*/

	/*
	* Grid Test end
	*/


	/*
	* Password Form START
	*/
	auto passwordField = std::make_unique<PasswordField>(490, 210, 100, 30, "PasswordField");
	auto submitButton = std::make_unique<Button>(600, 210, 100, 30);
	submitButton->SetText(L"Submit");
    submitButton->SetComponentName("SubmitButton");
	auto resultLabel = std::make_unique<Label>(490, 250, 100, 50, "resultLabel");


	auto submiter = new FormSubmiter(*resultLabel, *passwordField);
	submitButton->AddMouseStateSubscriber(*submiter);
	/*
	* Password Form END
	*/

	/*
	* SCROLLBAR TEST START
	*/

	for (int i = 0; i < 10; i++)
	{
		auto scrollBarTest = std::make_unique<Label>(0, 10 + 110 * i, 100, 100, "testLabel");

		scrollBarTest->SetText(L"TestLabel " + to_wstring(i));
		panel->Add(std::move(scrollBarTest));
	}

	/*
	* SCROLL BAR TEST END
	*/

	auto radioButton1 = std::make_unique<RadioButton>(600, 100, 100, 30, "radioButton1");
	auto radioButton2 = std::make_unique<RadioButton>(600, 135, 100, 30, "radioButton2");
	auto radioButton3 = std::make_unique<RadioButton>(600, 170, 100, 30, "radioButton3");

	auto radioButtonG1 = std::make_unique<RadioButton>(490, 100, 100, 30, "radioButtonG1");
	auto radioButtonG2 = std::make_unique<RadioButton>(490, 135, 100, 30, "radioButtonG2");
	auto radioButtonG3 = std::make_unique<RadioButton>(490, 170, 100, 30, "radioButtonG3");

	radioButton1->AddRadioButtonStateSubscriber(*radioButtonTester);
	radioButton2->AddRadioButtonStateSubscriber(*radioButtonTester);
	radioButton3->AddRadioButtonStateSubscriber(*radioButtonTester);

	radioButtonG1->AddRadioButtonStateSubscriber(*radioButtonTester);
	radioButtonG2->AddRadioButtonStateSubscriber(*radioButtonTester);
	radioButtonG3->AddRadioButtonStateSubscriber(*radioButtonTester);

    auto groupLabel1 = std::make_unique<Label>(600, 60, 100, 30, "Group1");
	groupLabel1->SetText(L"Group 1 buttons");
    auto groupLabel2 = std::make_unique<Label>(490, 60, 100, 30, "Group2");
	groupLabel2->SetText(L"Group 2 buttons");

	radioButton1->SetText(L"First");
	radioButton2->SetText(L"Second");
	radioButton3->SetText(L"Third");

	radioButtonG1->SetText(L"First");
	radioButtonG2->SetText(L"Second");
	radioButtonG3->SetText(L"Third");

	radioButton1->AddToGroup(*radioButton2);
	radioButton2->AddToGroup(*radioButton3);

	radioButtonG1->AddToGroup(*radioButtonG2);
	radioButtonG2->AddToGroup(*radioButtonG3);


	auto input = std::make_unique<TextInput>(500, 500, 200, 100, "input");
	input->SetText(L"おはよお");

	auto checkbox = std::make_unique<Checkbox>(600, 20, 105, 35, "Checkbox1");
	checkbox->SetText(L"Test checkbox");
	checkbox->AddCheckboxStateSubscriber(*checkboxTester);

	input->SetMultiline(true);

	frame = Window::Create(800, 600, 800, 600, "testFrame");
	frame->Add(std::move(input));
	frame->Add(std::move(checkbox));

	frame->Add(std::move(radioButton1));
	frame->Add(std::move(radioButton2));
	frame->Add(std::move(radioButton3));

	frame->Add(std::move(radioButtonG1));
	frame->Add(std::move(radioButtonG2));
	frame->Add(std::move(radioButtonG3));
	frame->Add(std::move(groupLabel1));
	frame->Add(std::move(groupLabel2));
	frame->Add(std::move(passwordField));
	frame->Add(std::move(resultLabel));
	frame->Add(std::move(submitButton));
	frame->Add(std::move(panel));
	frame->Add(std::move(mainTestGrid));
	frame->Add(std::move(fileBrowseButton));
	frame->Add(std::move(fileOutput));
	frame->Add(std::move(fileSaveButton));
	frame->Add(std::move(clearButton));
	frame->Add(std::move(listBox));
	frame->Add(std::move(listBoxDragTest));



	auto calculatorGridPtr = std::make_unique<Grid>(10, 10, 208, 208);
    auto* calculatorGridRef = calculatorGridPtr.get();
	calculatorGridRef->SetGridColumns({50, 50, 50, 50 });
	calculatorGridRef->SetGridRows({50, 50, 50, 50 });
	calculatorGridRef->AddColumnSpan(0, 3);
	calculatorGridRef->SetColumnGap(2);
	calculatorGridRef->SetRowGap(2);
	calculatorGridRef->AddKeyStateSubscriber(*inputTest);
	calculatorGridRef->SetComponentName("CalculatorGrid");

	auto outputLabelPtr = std::make_unique<Label>(offset, offset - height - gap, width * 3 + gap * 3, height, "outputLabel");
    auto* outputLabel = outputLabelPtr.get();

	calculatorGridRef->Add(std::move(outputLabelPtr));
	SimpleCalculator* calculator = new SimpleCalculator(*outputLabel);


	for (int i = 0; i < 11; i++)
	{
		auto inputButtonPtr = std::make_unique<Button>(0, 0, 0, 0);
        auto* inputButton = inputButtonPtr.get();
		inputButton->SetText(to_wstring(i));
		if (i == 3)
			inputButton->SetText(L"Add");
		if (i == 7)
			inputButton->SetText(L"Multiply");
		calculatorGridRef->Add(std::move(inputButtonPtr));
		inputButton->AddMouseStateSubscriber(*calculator);
	}

    frame->Add(std::move(calculatorGridPtr));
    auto& UiElementNode = frame->GetUiElementNode().GetNode(0);
}
