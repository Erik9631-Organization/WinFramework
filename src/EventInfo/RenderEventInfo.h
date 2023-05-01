#pragma once
#include "api/RenderCommander.h"
#include "Event.h"

class RenderingPool;

/**
 * This class contains all the information related to render events
 */

class RenderEventInfo : public Event
{
private:
    RenderingPool* renderer;
    EventSource* source;
public:
	/**
	 * The parent viewPortPosition is set ti 0,0 by default.
	 * \param g pointer to a renderer object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	explicit RenderEventInfo(RenderingPool *g, EventSource *source);

	/**
	 * \return Returns a pointer to renderer object to which it is possible to perform a drawing operation.
	 */
	[[nodiscard]] RenderingPool * GetRenderer() const;

    [[nodiscard]] EventSource * GetSource() const override;

};
