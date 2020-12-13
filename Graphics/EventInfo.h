#pragma once
class Component;
class EventInfo
{
protected:
	Component & component;
public:
	Component & GetComponent();
	EventInfo(Component & component);
	~EventInfo();
};

