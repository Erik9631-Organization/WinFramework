#pragma once
#include <any>
class Checkbox;
class EventCheckboxStateInfo
{
private:
	bool state;
	std::any src;
public:
	EventCheckboxStateInfo(std::any src, bool state);
	bool GetState();
	std::any GetSrc();
};

