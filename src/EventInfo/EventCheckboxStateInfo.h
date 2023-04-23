#pragma once
#include <any>
class Checkbox;
class CheckboxStateSubject;

/**
 * Class responsible for containing event data related to Checkbox
 */
class EventCheckboxStateInfo
{
private:
	bool state;
	CheckboxStateSubject* src;
public:
	/**
	 * \param src the source object that called the event
	 * \param state the state whether of the checkbox. True if checkbox is checked, false if unchecked.
	 */
	EventCheckboxStateInfo(CheckboxStateSubject* src, bool state);

	/**
	 * \return returns the state of the checkbox. True if checked, false if unchecked.
	 */
	bool GetState();

	/**
	 * \return returns pointer to the src object. It is encouraged to cast it to the type you expect to receive.
	 */
	CheckboxStateSubject* GetSrc();
};

