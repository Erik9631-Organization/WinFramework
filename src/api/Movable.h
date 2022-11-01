#pragma once
#include "Events/MoveSubject.h"
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
	virtual glm::vec2 GetPosition() = 0;

	/**
	 * Gets the X position of the object
	 * \return returns X position of the object as an integer.
	 */
	virtual float GetX() = 0;

	/**
	 * Gets the Y position of the object
	 * \return returns Y position of the object as an integer.
	 */
	virtual float GetY() = 0;

	/**
	 * Gets Absolute X position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns X absolute position of the object as an integer.
	 */
	virtual float GetAbsoluteX() = 0;
	
	/**
	 * Gets Absolute Y position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns Y absolute position of the object as an integer.
	 */
	virtual float GetAbsoluteY() = 0;

	/**
	 * Gets Absolute position of the object. The absolute position is always the position in the window regardless the parent.
	 * \return returns absolute position as a point which specifies the X and Y position.
	 */
	virtual glm::vec2 GetAbsolutePosition() = 0;

	/**
	 * Sets the position of the object.
	 * \param position Sets the position as a point which specifies the X and Y position.
	 */
	virtual void SetPosition(const glm::vec2 &position, bool emit) = 0;
    virtual void SetPosition(const glm::vec2 &position) = 0;

	/**
	 * Sets the position of the object. 
	 * \param x sets the X position of the object.
	 * \param y sets the Y position of the object.
	 */
	virtual void SetPosition(float x, float y, bool emit) = 0;
    virtual void SetPosition(float x, float y) = 0;

	/**
	 * Sets the position of the object.
	 * \param x sets the X position of the object.
	 */
	virtual void SetX(float x, bool emit) = 0;
    virtual void SetX(float x) = 0;

	/**
	 * Sets the position of the object.
	 * \param y sets the Y position of the object.
	 */
	virtual void SetY(float y, bool emit) = 0;
    virtual void SetY(float y) = 0;


	/**
	 * Sets position from the current position
	 * \param offset sets the position via a point object which specifies the X and Y position.
	 */
	virtual void SetTranslate(const glm::vec2 &offset, bool emit) = 0;
    virtual void SetTranslate(const glm::vec2 &offset) = 0;

	/**
	 * Sets position from the current position
	 * \param x specifies the X position.
	 */
	virtual void SetTranslateX(float x, bool emit) = 0;
    virtual void SetTranslateX(float x) = 0;

	/**
	 * Sets position from the current position
	 * \param y specifies the Y position.
	 */
	virtual void SetTranslateY(float y, bool emit) = 0;

    virtual void SetTranslateY(float y) = 0;

	/**
	 * Gets the element position dependent on the current position.
	 * \return returns the point which specifies the X and Y position.
	 */
	virtual glm::vec2 GetTranslate() = 0;

	/**
	 * Gets the element X position dependent on the current position.
	 * \return return the X position.
	 */
	virtual float GetTranslateX() = 0;

	/**
	 * Gets the element Y position dependent on the current position.
	 * \return return the Y position.
	 */
	virtual float GetTranslateY() = 0;
};

