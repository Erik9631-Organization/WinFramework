#pragma once
class EventMouseStateInfo;
class MouseStateSubscriber;
/**
 * This interface is implemented by classes which can be observed for mouse events.
 */
class MouseStateSubject
{
public:
	/**
	 * Recieves event whenever the left mouse button is down
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) = 0;

	/**
	 * Recieves event whenever the left mouse button is up
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) = 0;

	/**
	 * Recieves event whenever the left mouse button is pressed
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) = 0;

	/**
	 * Recieves event whenever the mouse hovers over the object.
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMouseHover(EventMouseStateInfo e) = 0;

	/**
	 * Recieves event whenever the mouse enters the component
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) = 0;

	/**
	 * Recieves event whenever the mouse leaves the component.
	 * \param e the event object to be received.
	 */
	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) = 0;

	virtual void NotifyOnMouseCapture(EventMouseStateInfo e) = 0;

	/**
	 * Adds a subscriber which can listen to mouse events.
	 * \param subscriber the subscriber which should be added to the event stream.
	 */
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;

	/**
	 * Removes a subscriber which can listen to mouse events.
	 * \param subscriber the subscriber which should be added to the event stream.
	 */
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;

	/**
	 * Returns whether the mouse is within the boundaries of the component.
	 * \return returns true if within the boundaries false if outside.
	 */
	virtual bool HasMouseEntered() = 0;

	virtual bool IsMouseCaptured() = 0;
};

