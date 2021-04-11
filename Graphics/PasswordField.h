#pragma once
#include "Component.h"
#include "Text.h"
#include "TextInputBehavior.h"

class PasswordField : public Component
{
private:
	Text text;
	wstring realText;
	Background background;
	SimpleBorder border;
	TextInputBehavior behavior;

public:
	PasswordField();
	PasswordField(int x, int y, int width, int height, string windowName);
	PasswordField(string name);

	void SetText(wstring text) override;
	wstring GetText() override;

	Color GetBackgroundColor();
	void SetBackgroundColor(Color color);
};

