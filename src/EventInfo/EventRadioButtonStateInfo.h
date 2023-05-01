#pragma once
#include <any>
#include "Event.h"

class RadioButtonStateSubject;

/**
 * This class is responsible for holding all the information related to radio thumbTrack events.
 */
class EventRadioButtonStateInfo : public Event
{
private:
	bool isSelected;
	EventSource* src;
public:
	/**
	 * \param selected whether the src object is selected. True for selected, false for unselected
	 * \param src the source object that called the event.
	 */
	EventRadioButtonStateInfo(bool selected, EventSource *src);

	/**
	 * \returns whether the src object was selected.
	 */
	[[nodiscard]] bool IsSelected() const;

    [[nodiscard]] EventSource * GetSource() const override;
};

