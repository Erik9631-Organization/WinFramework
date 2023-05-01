#pragma once
class Draggable;

class EventOnDragInfo
{
private:
	Draggable& src;
public:
	explicit EventOnDragInfo(Draggable& src);
	Draggable& GetSrc();
	
};
