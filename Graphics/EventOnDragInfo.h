#pragma once
class Draggable;

class EventOnDragInfo
{
private:
	Draggable& src;
public:
	EventOnDragInfo(Draggable& src);
	Draggable& GetSrc();
	
};

