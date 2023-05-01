#pragma once
#include <utility>
template <class type>
class EventOnAddInfo
{
private:
	type* addedElement;
public:
	explicit EventOnAddInfo(type* element)
	{
        addedElement = element;
	}

	type* GetAddedComponent()
	{
		return addedElement;
	}
};