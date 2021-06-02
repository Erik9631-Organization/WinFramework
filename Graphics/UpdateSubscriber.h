#pragma once
class EventUpdateInfo;

/**
 * This interface is implemented by all the classes which can recieve update events.
 */
class UpdateSubscriber
{
public:
	/**
	 * Recieves an update event and executes the update action. The flags are defined in EventUpdateInfo class.
	 */
	virtual void OnUpdate(EventUpdateInfo e) = 0;
};

