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
	glm::vec2 position;
	Movable* src;
public:
	/**
	 * \return Returns the position of the source object at the point this event was called.
	 */
    glm::vec2 GetPosition() const;

	/**
	 * \return returns the source object that called the event.
	 */
	Movable* GetSrc() const;

	/**
	 * \param position the position of the source object.
	 * \param src the source object that called the event. 
	 */
	EventMoveInfo(glm::vec2 position, Movable* src);
	~EventMoveInfo();
};

