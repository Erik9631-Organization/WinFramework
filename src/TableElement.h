#pragma once
#include "Components/Label.h"
#include <any>

class TableElement : public Label
{
private:
	bool selected = false;
	std::any value;
	glm::vec3 highlightColor;
	glm::vec3 originalcolor;
public:
	TableElement();
	TableElement(std::string name);
	TableElement(int x, int y, int width, int height, std::string name);

	void SetValue(std::any value);
	std::any GetValue();
	bool IsSelected();
	void SetSelected(bool selected);

};

