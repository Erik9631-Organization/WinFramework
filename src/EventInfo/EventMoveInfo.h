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
	glm::vec3 position{};
    glm::vec3 absolutePosition{};
	Movable* src;
    bool isOrigin = true;
public:
	/**
	 * \return Returns the viewPortSize of the source object at the point this event was called.
	 */
    [[nodiscard]] const glm::vec3 & GetPosition() const;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const;

    [[nodiscard]] bool IsOrigin() const;

	/**
	 * \return returns the source object that called the event.
	 */
	[[nodiscard]] Movable* GetSrc() const;

    EventMoveInfo(const glm::vec3 &position, const glm::vec3 &absolutePosition, Movable *src, bool isOrigin = true);
};

