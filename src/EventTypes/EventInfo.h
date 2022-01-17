#pragma once
class Component;

/**
 * \deprecated Deprecated. Subject for removal.
 */
class EventInfo
{
protected:
	Component & component;
public:
	Component & GetComponent();
	EventInfo(Component & component);
	~EventInfo();
};

