#pragma once
template <class type>
class EventOnAddInfo
{
private:
	type addedElement;
public:
	EventOnAddInfo(type element) : addedElement(element)
	{

	}

	type GetAddedComponent()
	{
		return addedElement;
	}
};