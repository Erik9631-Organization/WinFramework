#pragma once
#include "GenericObj.h"
#include "Event.h"
#include <glm.hpp>

class UiElement;
class Movable;
/**
 * This class is responsible for holding event data related to movement.
 */
class EventMoveInfo : public Event
{
private:
	glm::vec3 position{};
    glm::vec3 absolutePosition{};
	EventSource* src;
    bool isOrigin = true;
public:
	/**
	 * \return Returns the viewPortSize of the source object at the point this event was called.
	 */
    [[nodiscard]] const glm::vec3 & GetPosition() const;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const;

    [[nodiscard]] bool IsOrigin() const;

    EventMoveInfo(const glm::vec3 &position, const glm::vec3 &absolutePosition, EventSource *src, bool isOrigin = true);

    [[nodiscard]] EventSource * GetSource() const override;
};

