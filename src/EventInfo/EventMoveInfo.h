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
    glm::vec4 absolutePosition;
    glm::vec4 prevAbsolutePosition;
	Movable* src;
    bool isSource = true;
public:
	/**
	 * \return Returns the viewPortSize of the source object at the point this event was called.
	 */
    [[nodiscard]] const glm::vec4 & GetPosition() const;

    [[nodiscard]] const glm::vec4 & GetAbsolutePosition() const;

    [[nodiscard]] bool IsSource() const;

	/**
	 * \return returns the source object that called the event.
	 */
	[[nodiscard]] Movable* GetSrc() const;

    EventMoveInfo(const glm::vec4 &position, const glm::vec4 &absolutePosition, const glm::vec4 &prevPosition,
                  const glm::vec4 &prevAbsolutePosition, Movable *src, bool isSource = true);

    ~EventMoveInfo();
};

