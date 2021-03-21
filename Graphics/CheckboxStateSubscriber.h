#pragma once

class EventCheckboxStateInfo;

class CheckboxStateSubscriber
{
public:
	virtual void OnChecked(EventCheckboxStateInfo e) = 0;
};

