#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Renderable.h"
#include "Vector2.h"

/**
 * This class contains all the information related to render events
 */

class RenderEventInfo
{
private:
	Renderer* renderer;
public:
	/**
	 * The parent size is set ti 0,0 by default.
	 * \param g pointer to a renderer object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	RenderEventInfo(Renderer *g);

	/**
	 * \return Returns a pointer to renderer object to which it is possible to perform a drawing operation.
	 */
    Renderer * GetRenderer() const;
};
