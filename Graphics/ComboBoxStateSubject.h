#pragma once
#include "EventComboBoxStateInfo.h"
class ComboBoxStateSubscriber;

class ComboBoxStateSubject
{
	virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e) = 0;
	virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e) = 0;
	virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e) = 0;
	
	virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) = 0;
	virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) = 0;

};

