#pragma once
#include "MoveSubject.h"
#include "glm.hpp"

// GetPosition().x = 345

/**
 * The interface should be implemented by all classes which should be able to move
 */
class Movable : public MoveSubject
{
public:
	/**
	 * Returns viewPortSize
	 * \return returns Point object that specifies the X viewPortSize and the Y viewPortSize
	 */
	virtual const glm::vec4 & GetPosition() = 0;

	/**
	 * Gets the X viewPortSize of the object
	 * \return returns X viewPortSize of the object as an integer.
	 */
	virtual float GetX() = 0;

	/**
	 * Gets the Y viewPortSize of the object
	 * \return returns Y viewPortSize of the object as an integer.
	 */
	virtual float GetY() = 0;

    /**
     * Gets the Z viewPortSize of the object
     * \return returns Z viewPortSize of the object as an integer.
     */
    virtual float GetZ() = 0;

    /**
     * Gets the W viewPortSize of the object
     * \return returns W viewPortSize of the object as an integer.
     */
    virtual float GetW() = 0;

	/**
	 * Gets Absolute X viewPortSize of the object. The absolute viewPortSize is always the viewPortSize in the window regardless the parent.
	 * \return returns X absolute viewPortSize of the object as an integer.
	 */
	virtual float GetAbsoluteX() = 0;
	
	/**
	 * Gets Absolute Y viewPortSize of the object. The absolute viewPortSize is always the viewPortSize in the window regardless the parent.
	 * \return returns Y absolute viewPortSize of the object as an integer.
	 */
	virtual float GetAbsoluteY() = 0;

	/**
	 * Gets Absolute viewPortSize of the object. The absolute viewPortSize is always the viewPortSize in the window regardless the parent.
	 * \return returns absolute viewPortSize as a point which specifies the X and Y viewPortSize.
	 */
	virtual const glm::vec4 & GetAbsolutePosition() = 0;

	/**
	 * Sets the viewPortSize of the object.
	 * \param position Sets the viewPortSize as a point which specifies the X and Y viewPortSize.
	 */
	virtual void SetPosition(glm::vec4 position, bool emit) = 0;
    virtual void SetPosition(glm::vec4 position) = 0;

	/**
	 * Sets the viewPortSize of the object.
	 * \param x sets the X viewPortSize of the object.
	 * \param y sets the Y viewPortSize of the object.
	 */
	virtual void SetPosition(float x, float y, float z, float w, bool emit) = 0;
    virtual void SetPosition(float x, float y, float z, float w) = 0;

	/**
	 * Sets the viewPortSize of the object.
	 * \param x sets the X viewPortSize of the object.
	 */
	virtual void SetX(float x, bool emit) = 0;
    virtual void SetX(float x) = 0;

	/**
	 * Sets the viewPortSize of the object.
	 * \param y sets the Y viewPortSize of the object.
	 */
	virtual void SetY(float y, bool emit) = 0;
    virtual void SetY(float y) = 0;

    /**
     * Sets the viewPortSize of the object.
     * \param z sets the Z viewPortSize of the object.
     */
    virtual void SetZ(float z, bool emit) = 0;
    virtual void SetZ(float z) = 0;

    /**
     * Sets the viewPortSize of the object.
     * \param w sets the W viewPortSize of the object.
     */
    virtual void SetW(float w, bool emit) = 0;
    virtual void SetW(float w) = 0;

	/**
	 * Sets viewPortSize from the current viewPortSize
	 * \param offset sets the viewPortSize via a point object which specifies the X and Y viewPortSize.
	 */
	virtual void SetTranslate(glm::vec4 offset, bool emit) = 0;
    virtual void SetTranslate(glm::vec4 offset) = 0;

	/**
	 * Sets viewPortSize from the current viewPortSize
	 * \param x specifies the X viewPortSize.
	 */
	virtual void SetTranslateX(float x, bool emit) = 0;
    virtual void SetTranslateX(float x) = 0;

	/**
	 * Sets viewPortSize from the current viewPortSize
	 * \param y specifies the Y viewPortSize.
	 */
	virtual void SetTranslateY(float y, bool emit) = 0;

    virtual void SetTranslateY(float y) = 0;

	/**
	 * Gets the element viewPortSize dependent on the current viewPortSize.
	 * \return returns the point which specifies the X and Y viewPortSize.
	 */
	virtual glm::vec4 GetTranslate() = 0;

	/**
	 * Gets the element X viewPortSize dependent on the current viewPortSize.
	 * \return return the X viewPortSize.
	 */
	virtual float GetTranslateX() = 0;

	/**
	 * Gets the element Y viewPortSize dependent on the current viewPortSize.
	 * \return return the Y viewPortSize.
	 */
	virtual float GetTranslateY() = 0;
};

