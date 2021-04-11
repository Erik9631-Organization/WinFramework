#pragma once
class EventRadioButtonStateInfo;
class RadioButtonStateSubscriber;

class RadioButtonStateSubject
{
public:
	virtual void NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e) = 0;
	virtual void AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber) = 0;
	virtual void RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber) = 0;
};

