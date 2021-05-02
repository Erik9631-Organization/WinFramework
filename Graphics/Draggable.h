#pragma once
#include <any>

class Draggable
{
public:
	virtual std::any GetDragContent() = 0;
};

