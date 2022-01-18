#pragma once
#include <Windows.h>
#include <gdiplus.h>

class Component;
class MouseStateSubject;

/**
 * This class is responsible for containing mouse event information.
 */
class EventMouseStateInfo
{
private:
	Gdiplus::Point position;
	Gdiplus::Point relativePosition;
	Component* src = nullptr; // Kept here for compatibility reasons
	MouseStateSubject* mouseSrc = nullptr; // Alternative source parameter
	bool recursive = true; // Notifies the topmost component on the position if there is any, if set to false, then only notifies the target
	int key;
public:
	/**
	 * \param position the position of the mouse
	 * \param relativePosition the position of the mouse within the boundaries of the component
	 * \param key the mouse key that was interacted with.
	 * \param src the source of the object that called the event.
	 */
	
	EventMouseStateInfo(Gdiplus::Point position, Gdiplus::Point relativePosition, int key, MouseStateSubject* src);

	/**
	 * The relative position is automatically calculated from the src component
	 * \param position the position of the mouse
	 * \param key the mouse key that was interacted with.
	 * \param src the source of the object that called the event.
	 */
	EventMouseStateInfo(Gdiplus::Point position, int key, Component* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, Component* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source and the relative position.
	 * \param relativePosition the new relative position.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, Gdiplus::Point relativePosition, MouseStateSubject* src);

	/**
	 * \return returns the mouse position within the window at the time the event was called.
	 */
	Gdiplus::Point GetMouseAbsolutePosition();

	/**
	 * \return returns the mouse position within the component at the time the event was called.
	 */
	Gdiplus::Point GetMousePosition();

	/**
	 * \return returns the X position of the mouse within the window.
	 */
	int GetAbsoluteMouseX();

	/**
	 * \return returns the Y position of the mouse within the window.
	 */
	int GetAbsoluteMouseY();

	/**
	 * \return returns the X position of the mouse within the component.
	 */
	int GetMouseX();

	/**
	 * \return returns the Y position of the mouse within the component.
	 */
	int GetMouseY();

	/**
	 * \return returns the mouse thumbTrack that was pressed at the time the event was called.
	 */
	int GetKey();

	/**
	 * \return returns the source object that called the event. It is encouraged to cast it to the object that is expected to be received via dynamic_cast
	 */
	MouseStateSubject* GetSrc();


	/*
	* Sets whether the event is supposed to be recursively propagated throughout the containment hierarchy. 
	* Set to false if you only want to send the event to the target object.
	* NOTE: This is implementation specific. Event only carries the information, by default the framework understands this parameter.
	* \param state setting the recursive options. False for only sending it to the target, true for recursive propagation.
	*/
	void SetRecursive(bool state);

	/**
	 * \return returns whether the event is recursively propagating itself throughout the containment hierarchy.
	 */
	bool IsRecursive();

};