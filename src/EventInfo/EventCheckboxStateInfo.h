#pragma once
#include <any>
#include "Event.h"

class Checkbox;
class CheckboxStateSubject;

/**
 * Class responsible for containing event data related to Checkbox
 */
class EventCheckboxStateInfo : public Event
{
private:
	bool state;
	CheckboxStateSubject* src;
    EventSource* source;
public:
	/**
	 * \param src the source object that called the event
	 * \param state the state whether of the checkbox. True if checkbox is checked, false if unchecked.
	 */
	EventCheckboxStateInfo(EventSource *src, bool state);

	/**
	 * \return returns the state of the checkbox. True if checked, false if unchecked.
	 */
	[[nodiscard]] bool GetState() const;

    [[nodiscard]] EventSource * GetSource() const override;
};

