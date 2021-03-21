#pragma once
#include "ActivateSubscriber.h"
#include "KeyStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
class TextInput;

class TextInputBehavior : public KeyStateSubscriber, public ActivateSubscriber
{
private:
	bool multiLineEnabled = false;
	TextInput& associatedTextInput;
	Gdiplus::Color originalColor;
	Gdiplus::Color activeColor;
	void InsertCharacter(EventKeyStateInfo e);
	void SetActiveBackground();
	void SetInactiveBackground();
	void RemoveLastChar();
public:
	TextInputBehavior(TextInput& textInput);

	void SetMultiline(bool state);
	bool IsMultiLine();

	// Inherited via KeyStateSubscriber
	virtual void OnKeyDown(EventKeyStateInfo e) override;
	virtual void OnKeyUp(EventKeyStateInfo e) override;
	virtual void OnKeyPressed(EventKeyStateInfo e) override;


	// Inherited via ActivateSubscriber
	virtual void OnActiveStateChanged(EventOnActivateInfo) override;

};

