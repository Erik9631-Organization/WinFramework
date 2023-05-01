#include "TextInputBehavior.h"
#include "EventKeyStateInfo.h"
#include "Components/TextInput.h"
#include "EventOnActivateInfo.h"
using namespace std;

void TextInputBehavior::InsertCharacter(EventKeyStateInfo e)
{
	wchar_t c = e.GetUnicodeKey();

	wstring text = associatedTextInput.GetText() + c;

	if (c == '\0')
		return;
	if (e.GetVirtualKey() == (int)InputManager::VirtualKeys::Return)
	{
		if (multiLineEnabled)
			text = associatedTextInput.GetText() + L"\r\n";
		else
			return;
	}


	if (e.GetVirtualKey() == (int)InputManager::VirtualKeys::Back)
		return RemoveLastChar();
	associatedTextInput.SetText(text);
}

void TextInputBehavior::SetActiveBackground()
{
	//originalColor = associatedTextInput.GetBackgroundColor();

	originalColor = associatedTextInput.GetBackgroundColor();
	associatedTextInput.SetBackgroundColor(activeColor);
	//associatedTextInput.SetBackgroundColor(activeColor);
}

void TextInputBehavior::SetInactiveBackground()
{
	associatedTextInput.SetBackgroundColor(originalColor);
}

void TextInputBehavior::RemoveLastChar()
{
	if (associatedTextInput.GetText().length() == 0)
		return;
	wstring input = associatedTextInput.GetText();
	input.pop_back();
	associatedTextInput.SetText(input);
}


TextInputBehavior::TextInputBehavior(TextInputApi &textInput) : associatedTextInput(textInput)
{
	activeColor = {255, 255, 255, 0};
	textInput.AddOnActivateSubscriber(*this);
	textInput.AddKeyStateSubscriber(*this);


	//originalColor = textInput.GetPropery<Gdiplus::Color>("get-background-color");

	//originalColor = textInput.GetBackgroundColor();
}

void TextInputBehavior::SetMultiline(bool state)
{
	multiLineEnabled = state;
}

bool TextInputBehavior::IsMultiLine()
{
	return multiLineEnabled;
}

void TextInputBehavior::OnKeyDown(EventKeyStateInfo e)
{
	InsertCharacter(e);
}

void TextInputBehavior::OnKeyUp(EventKeyStateInfo e)
{

}

void TextInputBehavior::OnKeyPressed(EventKeyStateInfo e)
{
	InsertCharacter(e);
}

void TextInputBehavior::OnActiveStateChanged(EventOnActivateInfo e)
{
	if (e.IsActive())
		SetActiveBackground();
	else
		SetInactiveBackground();

}