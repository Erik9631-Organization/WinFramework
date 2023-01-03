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
	 * The parent size is set ti 0,0 by default.
	 * \param g pointer to a rendereringProvider object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	RenderEventInfo(RenderingPool *g);

	/**
	 * \return Returns a pointer to rendereringProvider object to which it is possible to perform a drawing operation.
	 */
	RenderingPool * GetRenderer() const;
private:
    RenderingPool* renderer;
};
