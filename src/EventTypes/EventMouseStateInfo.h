#pragma once
#include <Vector2.h>

class UiElement;
class MouseStateSubject;

/**
 * This class is responsible for containing mouse event information.
 */
class EventMouseStateInfo
{
private:
	Vector2 position;
	Vector2 relativePosition;
	UiElement* src = nullptr; // Kept here for compatibility reasons
	MouseStateSubject* mouseSrc = nullptr; // Alternative source parameter
	Vector2 mouseDelta;
	bool recursive = true; // Notifies the topmost component on the position if there is any, if set to false, then only notifies the target
	int key;
public:

    Vector2 GetMouseDelta();

    EventMouseStateInfo(Vector2 position, Vector2 relativePosition, Vector2 delta, int key, MouseStateSubject* src);

	/**
	 * The relative position is automatically calculated from the src component
	 * \param position the position of the mouse
	 * \param key the mouse key that was interacted with.
	 * \param src the source of the object that called the event.
	 */

	EventMouseStateInfo(Vector2 position, int key, UiElement* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, UiElement* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source and the relative position.
	 * \param relativePosition the new relative position.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, Vector2 relativePosition, MouseStateSubject* src);

	/**
	 * \return returns the mouse position within the window at the time the event was called.
	 */
	Vector2 GetMouseAbsolutePosition();

	/**
	 * \return returns the mouse position within the component at the time the event was called.
	 */
	Vector2 GetMousePosition();

	/**
	 * \return returns the X position of the mouse within the window.
	 */
	float GetAbsoluteMouseX();

	/**
	 * \return returns the Y position of the mouse within the window.
	 */
	float GetAbsoluteMouseY();

	/**
	 * \return returns the X position of the mouse within the component.
	 */
	float GetMouseX();

	/**
	 * \return returns the Y position of the mouse within the component.
	 */
	float GetMouseY();

	/**
	 * \return returns the mouse thumbTrack that was pressed at the time the event was called.
	 */
	int GetKey();

	/**
	 * \return returns the source object that called the event. It is encouraged to cast it to the object that is expected to be received via dynamic_cast
	 */
	MouseStateSubject* GetSrc();


	/**
	* Sets whether the event is supposed to be recursively propagated throughout the containment hierarchy. 
	* Set to false if you only want to send the event to the target object.
	* \remark This is implementation specific. Event only carries the information, by default the framework understands this parameter.
	* \param state setting the recursive options. False for only sending it to the target, true for recursive propagation.
	*/
	void SetRecursive(bool state);

	/**
	 * \return returns whether the event is recursively propagating itself throughout the containment hierarchy.
	 */
	bool IsRecursive();

};