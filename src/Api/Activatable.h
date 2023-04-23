#pragma once
#include "Events/ActivateSubject.h"

/**
 * This interface is implemented by objects which support focus. By definition, only one component at the same time can have focus
 * And the component that has focus receives input events.
 */
class Activatable : public virtual ActivateSubject
{
public:
	/**
	 * Sets whether the current component should have focus.
	 * \param state true if it should have focus, false if it should not.
	 */
	virtual void SetActive(bool state) = 0;

	/**
	 * Returns whether the component has a focus
	 * \return returns whether the component is active. True for active false for inactive.
	 */
	virtual bool IsActive() = 0;
};

