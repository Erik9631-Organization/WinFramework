#pragma once
#include "Panel.h"
#include "Grid.h"
#include "TrackBar.h"
#include "DefaultListBoxBehavior.h"
#include <any>

class ListBox : public Panel
{
private:
	Grid layout;
	TrackBar trackbar;
	DefaultListBoxBehavior behavior;

public:
	ListBox();
	ListBox(std::string name);
	ListBox(int x, int y, int width, int height, std::string name);
	std::vector<TableElement*>GetElements();
	void CreateListElement(std::wstring name, std::any value);
	void Add(Component& component) override;
};
