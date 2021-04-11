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

	type& EventOnAddInfo<type>::GetAddedComponent()
	{
		return addedElement;
	}
};