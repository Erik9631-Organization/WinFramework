#pragma once
#include "EventInfo.h"
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
    glm::vec4 size;
	Resizable* src;

public:
	/**
	 * \return returns the viewPortPosition of the source at the point the event was called.
	 */
    glm::vec4 GetSize() const;

	/**
	 * \return returns source object that performed the call.
	 */
	Resizable* GetSrc() const;

	/**
	 * \param size the viewPortPosition of the source object
	 * \param src the source object that that called the event.
	 */
	EventResizeInfo(glm::vec4 size, Resizable* src);
	~EventResizeInfo();
};

