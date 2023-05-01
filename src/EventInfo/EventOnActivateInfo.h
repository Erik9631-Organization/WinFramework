#pragma once

#include "Event.h"

/**
 * This class is responsible for holding data related to Activate events.
 */
class EventOnActivateInfo : public Event
{
private:
	bool state;
    EventSource* source = nullptr;
public:
	/**
	 * \param state the activation state at the point the event was called. True means it has focus, false means it doesn't.
	 */
	explicit EventOnActivateInfo(bool state, EventSource *source);

	/**
	 * \return returns the activation state of the object.
	 */
	[[nodiscard]] bool IsActive() const;

    [[nodiscard]] EventSource * GetSource() const override;
};

