#pragma once
class UiElement;

/**
 * \deprecated Deprecated. Subject for removal.
 */
class EventInfo
{
protected:
	UiElement & component;
public:
	UiElement & GetComponent();
	EventInfo(UiElement & component);
	~EventInfo();
};

