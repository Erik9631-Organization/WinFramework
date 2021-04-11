#pragma once
class EventRadioButtonStateInfo;

class RadioButtonStateSubscriber
{
public:
	virtual void OnRadioButtonSelected(EventRadioButtonStateInfo e) = 0;
};

