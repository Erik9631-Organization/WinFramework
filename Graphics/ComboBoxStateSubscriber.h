#pragma once
#include "EventComboBoxStateInfo.h"
class ComboBoxStateSubscriber
{
public:
	virtual void OnComboBoxOpened(EventComboBoxStateInfo e) = 0;
	virtual void OnComboBoxClosed(EventComboBoxStateInfo e) = 0;
	virtual void OnSelectionChanged(EventComboBoxStateInfo e) = 0;
};

