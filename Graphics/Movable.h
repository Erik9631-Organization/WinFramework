#pragma once
#include "MoveSubject.h"
#include <Windows.h>
#include <gdiplus.h>

/**
 * The interface should be implemented by all classes which should be able to move
 */
class Movable : public MoveSubject
{
public:
	/**
	 * Returns position
	 * \return returns Point object that specifies the X position and the Y position
	 */
	virtual Gdiplus::Point GetPosition() = 0;

	/**
	 * Gets the X position of the object
	 * \return returns X position of the object as an integer.
	 */
	virtual int GetX() = 0;

	/**
	 * Gets the Y position of the object
	 * \return returns Y position of the object as an integer.
	 */
	virtual int GetY() = 0;

	/**
	 * Gets Absolute X position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns X absolute position of the object as an integer.
	 */
	virtual int GetAbsoluteX() = 0;
	
	/**
	 * Gets Absolute Y position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns Y absolute position of the object as an integer.
	 */
	virtual int GetAbsoluteY() = 0;

	/**
	 * Gets Absolute position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns absolute position as a point which specifies the X and Y position.
	 */
	virtual Gdiplus::Point GetAbsolutePosition() = 0;

	/**
	 * Sets the position of the object.
	 * \param position Sets the position as a point which specifies the X and Y position.
	 */
	virtual void SetPosition(Gdiplus::Point position) = 0;

	/**
	 * Sets the position of the object. 
	 * \param x sets the X position of the object.
	 * \param y sets the Y position of the object.
	 */
	virtual void SetPosition(int x, int y) = 0;

	/**
	 * Sets the position of the object.
	 * \param x sets the X position of the object.
	 */
	virtual void SetX(int x) = 0;

	/**
	 * Sets the position of the object.
	 * \param y sets the Y position of the object.
	 */
	virtual void SetY(int y) = 0;


	/**
	 * Sets offset from the current position
	 * \param offset sets the offset via a point object which specifies the X and Y offset.
	 */
	virtual void SetElementOffset(Gdiplus::Point offset) = 0;

	/**
	 * Sets offset from the current position
	 * \param x specifies the X offset.
	 */
	virtual void SetElementXOffset(int x) = 0;

	/**
	 * Sets offset from the current position
	 * \param y specifies the Y offset.
	 */
	virtual void SetElementYOffset(int y) = 0;

	/**
	 * Gets the element offset dependent on the current position.
	 * \return returns the point which specifies the X and Y offset.
	 */
	virtual Gdiplus::Point GetElementOffset() = 0;

	/**
	 * Gets the element X offset dependent on the current position.
	 * \return return the X offset.
	 */
	virtual int GetElementXOffset() = 0;

	/**
	 * Gets the element Y offset dependent on the current position.
	 * \return return the Y offset.
	 */
	virtual int GetElementYOffset() = 0;
};

