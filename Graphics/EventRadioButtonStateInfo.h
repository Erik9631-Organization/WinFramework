#pragma once
#include <any>

class EventRadioButtonStateInfo
{
private:
	bool isSelected;
	std::any src;
public:
	EventRadioButtonStateInfo(bool selected, std::any src);
	std::any GetSrc();
	bool IsSelected();
};

