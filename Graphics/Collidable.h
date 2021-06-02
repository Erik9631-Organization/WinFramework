#pragma once
#include <any>
namespace Gdiplus
{
	class Point;
}

/**
 * This interface is implemented by all the classes which support collision check.
 */
class Collidable
{
public:
	/**
	 * Returns whether a component within the window collides with the specified point
	 * \param point the point to check the collision with
	 * \return returns true if there is a collision, false if there is no collision
	 */
	virtual bool ColidesWithPoint(Gdiplus::Point point) = 0;

	/**
	 * Returns a component within the window that collides with the specified point
	 * \param point the point to check the collision with
	 * \return The return value is implementation specific and therefore returns generic std::any. In case of the standard components, it is always a pointer to component (Component*)
	 * Use std::any_cast<Component*> if casting in the standard implementation.
	 */
	virtual std::any ColidesWithUpmost(Gdiplus::Point point) = 0;
};

