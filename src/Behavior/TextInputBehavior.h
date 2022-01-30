#pragma once
#include "Events/ActivateSubscriber.h"
#include "Events/KeyStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include "Vector4.h"

class UiElement;

class TextInput;

class TextInputBehavior : public KeyStateSubscriber, public ActivateSubscriber
{
private:
	bool multiLineEnabled = false;
	UiElement& associatedTextInput;
	Vector4 originalColor;
	Vector4 activeColor;
	void InsertCharacter(EventKeyStateInfo e);
	void SetActiveBackground();
	void SetInactiveBackground();
	void RemoveLastChar();
public:
	TextInputBehavior(UiElement& textInput);

	void SetMultiline(bool state);
	bool IsMultiLine();

	// Inherited via KeyStateSubscriber
	virtual void OnKeyDown(EventKeyStateInfo e) override;
	virtual void OnKeyUp(EventKeyStateInfo e) override;
	virtual void OnKeyPressed(EventKeyStateInfo e) override;


	// Inherited via ActivateSubscriber
	virtual void OnActiveStateChanged(EventOnActivateInfo) override;

};

