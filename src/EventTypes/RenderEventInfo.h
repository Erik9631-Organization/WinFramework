#pragma once
#include <Windows.h>
#include <gdiplus.h>

/**
 * This class contains all the information related to render events
 */

class RenderEventInfo
{
private:
	Gdiplus::Graphics* graphics;
	Gdiplus::Size parentSize;
	Gdiplus::Point parentPosition;
public:
	/**
	 * \param g pointer to a graphics object associated with a HDC on which it is possible to perform a drawing operation.
	 * \param parentSize additional information specifying the size of the parent.
	 */
	RenderEventInfo(Gdiplus::Graphics* g, Gdiplus::Size parentSize, Gdiplus::Point parentPosition);

	/**
	 * The parent size is set ti 0,0 by default.
	 * \param g pointer to a graphics object associated with a HDC on which it is possible to perform a drawing operation.
	 */
	RenderEventInfo(Gdiplus::Graphics* g);

	/**
	 * \return Returns a pointer to graphics object to which it is possible to perform a drawing operation.
	 */
	Gdiplus::Graphics* GetGraphics();

	/**
	 * \return returns the size of the parent.
	 */
	Gdiplus::Size GetParentSize();

	/**
	 * \param parentSize sets the information about the size of the parent.
	 */
	void SetParentSize(Gdiplus::Size parentSize);

	Gdiplus::Point GetParentPosition();
};
