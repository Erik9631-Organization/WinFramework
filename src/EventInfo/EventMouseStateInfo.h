#pragma once
#include <glm.hpp>
#include "Event.h"

class UiElement;
class MouseStateSubject;

/**
 * This class is responsible for containing mouse event information.
 */
class EventMouseStateInfo : public Event
{
private:
    glm::vec3 position{0};
    glm::vec3 relativePosition{0};
	EventSource* src = nullptr; // Kept here for compatibility reasons
    glm::vec3 mouseDelta{0};
	bool recursive = true; // Notifies the topmost component on the viewPortSize if there is any, if set to false, then only notifies the target
	int key;
public:

    glm::vec3 GetMouseDelta();

    EventMouseStateInfo(glm::vec3 position, glm::vec3 relativePosition, glm::vec3 delta, int key, EventSource *src);

	/**
	 * Copies an existing EventMouseStateInfo object but lets the user redefine the source and the relative viewPortSize.
	 * \param relativePosition the new relative viewPortSize.
	 * \param src the new source object that called the event.
	 */
	EventMouseStateInfo(EventMouseStateInfo e, glm::vec3 relativePosition, EventSource *src);

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
	float GetAbsoluteMouseX() const;

	/**
	 * \return returns the Y viewPortSize of the mouse within the window.
	 */
	float GetAbsoluteMouseY() const;

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


    //TODO Remove. This shouldn't exist and nobody should care.
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

    [[nodiscard]] EventSource * GetSource() const override;

};