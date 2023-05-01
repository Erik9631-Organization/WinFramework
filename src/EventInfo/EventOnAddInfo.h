#pragma once
#include <utility>
#include "Event.h"

template <class type>
class EventOnAddInfo : public Event
{
private:
	type* addedElement;
    EventSource* source = nullptr;
public:
	explicit EventOnAddInfo(type *element, EventSource *src)
	{
        addedElement = element;
        this->source = src;
	}

	type* GetAddedComponent()
	{
		return addedElement;
	}

    [[nodiscard]] EventSource * GetSource() const override
    {
        return source;
    }
};