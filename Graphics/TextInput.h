#pragma once
#include "Component.h"
#include "Text.h"
#include "Background.h"
#include "TextInputBehavior.h"
#include "SimpleBorder.h"
class TextInput : public Component
{
private:
	Background background;
	SimpleBorder border;
	Text text;
	TextInputBehavior inputBehavior;

public:
	TextInput();
	TextInput(int x, int y, int width, int height, string windowName);
	TextInput(string name);
	void SetText(wstring text);
	wstring GetText();
	Color GetBackgroundColor();
	void SetMultiline(bool state);
	bool IsMultiLine();
	void SetBackgroundColor(Color color);
};

