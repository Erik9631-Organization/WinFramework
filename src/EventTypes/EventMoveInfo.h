#pragma once
#include "EventInfo.h"
#include "GenericObj.h"
#include <glm.hpp>

class UiElement;
class Movable;
/**
 * This class is responsible for holding event data related to movement.
 */
class EventMoveInfo
{
private:
    glm::vec4 prevPosition;
	glm::vec4 position;
	Movable* src;
public:
    const glm::vec4& GetPrevPosition() const;

	/**
	 * \return Returns the position of the source object at the point this event was called.
	 */
    glm::vec4 GetPosition() const;

	/**
	 * \return returns the source object that called the event.
	 */
	Movable* GetSrc() const;

	/**
	 * \param position the position of the source object.
	 * \param src the source object that called the event. 
	 */
	EventMoveInfo(glm::vec4 position, Movable* src);
    EventMoveInfo(glm::vec4 position, glm::vec4 prevPosition, Movable* src);

    ~EventMoveInfo();
};

