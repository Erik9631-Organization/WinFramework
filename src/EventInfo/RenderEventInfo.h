#pragma once
#include "api/RenderCommander.h"

class RenderingPool;

/**
 * This class contains all the information related to render events
 */

class RenderEventInfo
{
public:
	/**
	 * The parent viewPortPosition is set ti 0,0 by default.
	 * \param g pointer to a renderer object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	RenderEventInfo(RenderingPool *g);

	/**
	 * \return Returns a pointer to renderer object to which it is possible to perform a drawing operation.
	 */
	RenderingPool * GetRenderer() const;
private:
    RenderingPool* renderer;
};
