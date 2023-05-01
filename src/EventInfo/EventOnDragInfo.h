#pragma once
#include "Event.h"

class Draggable;

class EventOnDragInfo : public Event
{
private:
	EventSource* src;
public:
	explicit EventOnDragInfo(EventSource *src);
    [[nodiscard]] EventSource * GetSource() const override;
};
