#pragma once
class Component;
class AddEventInfo;

class OnAddListener
{
public:
	virtual void OnAdd(AddEventInfo eventInfo) = 0;
	OnAddListener();
	~OnAddListener() {};
};

