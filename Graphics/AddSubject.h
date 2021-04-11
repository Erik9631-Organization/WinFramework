#pragma once

template<class T>
class OnAddSubscriber;

template<class T>
class EventOnAddInfo;

template<class type>
class AddSubject
{
	virtual void NotifyOnAddInfo(EventOnAddInfo<type> e) = 0;
	virtual void AddOnAddSubscriber(OnAddSubscriber<type>& subscriber) = 0;
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<type>& subscriber) = 0;
};

