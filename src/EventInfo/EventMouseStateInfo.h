#pragma once
#include <glm.hpp>

class UiElement;
class MouseStateSubject;

/**
 * This class is responsible for containing mouse event information.
 */
class EventMouseStateInfo
{
private:
    glm::vec3 position;
    glm::vec3 relativePosition;
	UiElement* src = nullptr; // Kept here for compatibility reasons
	MouseStateSubject* mouseSrc = nullptr; // Alternative source parameter
    glm::vec3 mouseDelta;
	bool recursive = true; // Notifies the topmost component on the viewPortSize if there is any, if set to false, then only notifies the target
	int key;
public:

    glm::vec3 GetMouseDelta();

    EventMouseStateInfo(glm::vec3 position, glm::vec3 relativePosition, glm::vec3 delta, int key, MouseStateSubject* src);

	/**
	 * The relative viewPortSize is automatically calculated from the src component
	 * \param position the viewPortSize of the mouse
	 * \param key the mouse key that was interacted with.
	 * \param src the source of the object that called the event.
	 */

	EventMouseStateInfo(glm::vec3 position, int key, UiElement* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, UiElement* src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source and the relative viewPortSize.
	 * \param relativePosition the new relative viewPortSize.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, glm::vec3 relativePosition, MouseStateSubject* src);

	/**
	 * \return returns the mouse viewPortSize within the window at the time the event was called.
	 */
    glm::vec3 GetMouseAbsolutePosition();

	/**
	 * \return returns the mouse viewPortSize within the component at the time the event was called.
	 */
    glm::vec3 GetMousePosition();

	/**
	 * \return returns the X viewPortSize of the mouse within the window.
	 */
	float GetAbsoluteMouseX();

	/**
	 * \return returns the Y viewPortSize of the mouse within the window.
	 */
	float GetAbsoluteMouseY();

	/**
	 * \return returns the X viewPortSize of the mouse within the component.
	 */
	float GetMouseX();

	/**
	 * \return returns the Y viewPortSize of the mouse within the component.
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