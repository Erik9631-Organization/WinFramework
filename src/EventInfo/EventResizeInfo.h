#pragma once
#include <any>
#include "GenericObj.h"
#include <glm.hpp>

class Resizable;
/**
 * This class is responsible for holding all the event information related to resizing
 */
class EventResizeInfo
{
private:
    glm::vec3 size;
	Resizable* src;

public:
	/**
	 * \return returns the viewPortPosition of the source at the point the event was called.
	 */
    [[nodiscard]] const glm::vec3 & GetSize() const;

	/**
	 * \return returns source object that performed the call.
	 */
	[[nodiscard]] Resizable* GetSrc() const;

	/**
	 * \param size the viewPortPosition of the source object
	 * \param src the source object that that called the event.
	 */
	EventResizeInfo(glm::vec3 size, Resizable* src);
	~EventResizeInfo();
};

