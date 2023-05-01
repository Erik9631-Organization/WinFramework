#pragma once
#include "EventComboBoxStateInfo.h"
class ComboBoxStateSubscriber;
/**
 * This interface is implemented by all objects which contain the combobox behavior.
 */
class ComboBoxStateSubject : public virtual EventSource
{
	/**
	 * Calls an event on all subscribers when the combobox is unpacked / opened.
	 * \param e event object containing information related to the combobox.
	 */
	virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e) = 0;

	/**
	 * Calls an event on all subscribers when the combobox is packed / closed.
	 * \param e event object containing information related to the combobox.
	 */
	virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e) = 0;

	/**
	 * Calls an event on all subscribers when the combobox selection is changed.
	 * \param e event object containing information related to the combobox.
	 */
	virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e) = 0;


	/**
	 * Adds a new subscriber to the combobox event stream.
	 * \param subscriber subscriber which is to be added to the event stream.
	 */
	virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) = 0;

	/**
	 * Removes a subscriber from the event stream
	 * \param subscriber subscriber which is to be removed from the event stream.
	 */
	virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) = 0;

};

