#pragma once
/**
 * This class is responsible for holding data related to Activate events.
 */
class EventOnActivateInfo
{
private:
	bool state;
public:
	/**
	 * \param state the activation state at the point the event was called. True means it has focus, false means it doesn't.
	 */
	EventOnActivateInfo(bool state);

	/**
	 * \return returns the activation state of the object.
	 */
	bool IsActive();
};

