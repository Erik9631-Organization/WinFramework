#pragma once
#include "Component.h"
#include "CircleBorder.h"
#include "SimpleBorder.h"
#include "RadioButtonGraphics.h"
#include "Text.h"
#include "RadioButtonBehavior.h"
#include <vector>
#include <memory>

class RadioButton : public Component
{
private:
	SimpleBorder border;
	RadioButtonGraphics radioButtonGraphics;
	RadioButtonBehavior behavior;
	Text text;
	
	Background background;
	//radioButtonBehavior
	bool checked = false;
public:
	void Check();
	bool IsChecked();
	void SetChecked(bool state);
	void AddToGroup(RadioButton& button);
	void SetGroup(std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group);
	void UnGroup();
	void SetText(std::wstring text);
	std::wstring GetText();

	RadioButton();
	RadioButton(std::string name);
	RadioButton(int x, int y, int width, int height, string componentName);
};

