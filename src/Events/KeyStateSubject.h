#pragma once
class EventKeyStateInfo;
class KeyStateSubscriber;

/**
 * This interface is implemented by all classes which are capable of sending KeyState events
 */
class KeyStateSubject
{
public:
	/**
	 * Sends an event to all subscribers on KeyDown.
	 * \param e the event object to be sent.
	 */
	virtual void NotifyOnKeyDown(EventKeyStateInfo e) = 0;

	/**
	 * Sends an event to all subscribers on KeyUp
	 * \param e the event object to be sent.
	 */
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) = 0;

	/**
	 * Sends an event to all subscribers whenever the key is held down.
	 * \param e the event object to be sent.
	 */
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) = 0;

	/**
	 * Adds a subscriber to the event stream.
	 * \param subscriber the subscriber to be added.
	 */
	virtual void AddKeyStateSubscriber(KeyStateSubscriber& subscriber) = 0;

	/**
	 * Removes a subscriber from the event stream
	 * \param subscriber the subscriber to be removed.
	 */
	virtual void RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber) = 0;
};

