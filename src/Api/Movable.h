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
	[[nodiscard]] virtual const glm::vec4 & GetPosition() const = 0;

	/**
	 * Gets Absolute viewPortSize of the object. The absolute viewPortSize is always the viewPortSize in the window regardless the parent.
	 * \return returns absolute viewPortSize as a point which specifies the X and Y viewPortSize.
	 */
	[[nodiscard]] virtual const glm::vec4 & GetAbsolutePosition() const = 0;

	/**
	 * Sets the viewPortSize of the object.
	 * \param position Sets the viewPortSize as a point which specifies the X and Y viewPortSize.
	 */
	virtual void SetPosition(const glm::vec4 &position, bool emit) = 0;

	/**
	 * Sets viewPortSize from the current viewPortSize
	 * \param offset sets the viewPortSize via a point object which specifies the X and Y viewPortSize.
	 */
	virtual void SetTranslate(const glm::vec4 &offset, bool emit) = 0;
	/**
	 * Gets the element viewPortSize dependent on the current viewPortSize.
	 * \return returns the point which specifies the X and Y viewPortSize.
	 */
	[[nodiscard]] virtual const glm::vec4 & GetTranslate() const = 0;
};
