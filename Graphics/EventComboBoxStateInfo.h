#pragma once
class ComboElement;
class ComboBoxStateSubject;

/**
 * This class is responsible for holding event information related to the combobox.
 */
class EventComboBoxStateInfo
{
private:
	ComboElement* element;
	ComboBoxStateSubject& src;
public:
	/**
	 * \param element the newly selected element in the combobox
	 * \param src the source object that called the event.
	 */
	EventComboBoxStateInfo(ComboElement* element, ComboBoxStateSubject& src);
	
	/**
	 * \return returns the element that was selected. 
	 */
	ComboElement* GetElement();
	
	/**
	 * \return returns the source object that called the event
	 */
	ComboBoxStateSubject& GetSrc();
};

