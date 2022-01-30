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
	Vector2 parentSize;
	Vector2 parentPosition;
public:
	/**
	 * \param renderer pointer to a renderer object associated with a HDC on which it is possible to perform a drawing operation.
	 * \param parentSize additional information specifying the size of the parent.
	 */
	RenderEventInfo(Renderer *renderer, Vector2 parentSize, Vector2 parentPosition);

	/**
	 * The parent size is set ti 0,0 by default.
	 * \param g pointer to a renderer object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	RenderEventInfo(Renderer *g);

	/**
	 * \return Returns a pointer to renderer object to which it is possible to perform a drawing operation.
	 */
    Renderer * GetRenderer() const;

	/**
	 * \return returns the size of the parent.
	 */
    Vector2 GetParentSize() const;

	/**
	 * \param parentSize sets the information about the size of the parent.
	 */
	void SetParentSize(Vector2 parentSize);

	Vector2 GetParentPosition() const;
};
