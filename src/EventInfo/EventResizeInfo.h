#pragma once
#include <any>
#include "GenericObj.h"
#include <glm.hpp>
#include "Event.h"

class Resizable;
/**
 * This class is responsible for holding all the event information related to resizing
 */
class EventResizeInfo : public Event
{
private:
    glm::vec3 size;
	EventSource* src;
public:
	/**
	 * \return returns the viewPortPosition of the source at the point the event was called.
	 */
    [[nodiscard]] const glm::vec3 & GetSize() const;

	/**
	 * \param size the viewPortPosition of the source object
	 * \param src the source object that that called the event.
	 */
	EventResizeInfo(glm::vec3 size, EventSource *src);
	~EventResizeInfo() override = default;

    EventSource * GetSource() const override;
};

