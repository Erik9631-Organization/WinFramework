#pragma once
template<class T>
class EventOnAddInfo;

template <class type>
class OnAddSubscriber
{
public:
	virtual void OnAdd(EventOnAddInfo<type> e) = 0;
};

