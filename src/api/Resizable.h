#pragma once
#include "Events/ResizeSubject.h"
#include <Vector2.h>
/**
 * An interface for all the classes that can be resized.
 * The interface also defines that every resizable has to support an event stream (Byt enforcing the ResizeSubject interface)
 */
class Resizable : public ResizeSubject
{
public:
	/**
	 * Returns the size of the object.
	 * \return returns a size object which specifies the width and height
	 */
	virtual Vector2 GetSize() = 0;

	/**
	 * Returns the width of the object
	 * \return returns the int value of the width
	 */
	virtual float GetWidth() = 0;
	
	/**
	 * Returns the height of the object
	 * \return returns the int value of the height
	 */
	virtual float GetHeight() = 0;
	
	/**
	 * Sets the size of the object
	 * \param size the size object which specifies the width and height of the target object.
	 */
	virtual void SetSize(Vector2 size, bool emit) = 0;
    virtual void SetSize(Vector2 size) = 0;
	
	/**
	 * Sets the Size of the object
	 * \param width parameter which should specify the width of the object.
	 * \param height parameter which should specify the height of the object.
	 */
	virtual void SetSize(float width, float height, bool emit) = 0;
    virtual void SetSize(float width, float height) = 0;

	/**
	 * Sets the Width of the object
	 * \param width parameter which should specify the width of the object.
	 */
	virtual void SetWidth(float width, bool emit) = 0;
    virtual void SetWidth(float width) = 0;
	
	/**
	 * Sets the Height of the object
	 * \param height parameter which should specify the height of the object.
	 */
	virtual void SetHeight(float height, bool emit) = 0;
    virtual void SetHeight(float height) = 0;
};

