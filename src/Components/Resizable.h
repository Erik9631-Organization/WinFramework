#pragma once
#include "Events/ResizeSubject.h"
#include <Windows.h>
#include <gdiplus.h>
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
	virtual Gdiplus::Size GetSize() = 0;

	/**
	 * Returns the width of the object
	 * \return returns the int value of the width
	 */
	virtual int GetWidth() = 0;
	
	/**
	 * Returns the height of the object
	 * \return returns the int value of the height
	 */
	virtual int GetHeight() = 0;
	
	/**
	 * Sets the size of the object
	 * \param size the size object which specifies the width and height of the target object.
	 */
	virtual void SetSize(Gdiplus::Size size) = 0;
	
	/**
	 * Sets the Size of the object
	 * \param width parameter which should specify the width of the object.
	 * \param height parameter which should specify the height of the object.
	 */
	virtual void SetSize(int width, int height) = 0;

	/**
	 * Sets the Width of the object
	 * \param width parameter which should specify the width of the object.
	 */
	virtual void SetWidth(int width) = 0;
	
	/**
	 * Sets the Height of the object
	 * \param height parameter which should specify the height of the object.
	 */
	virtual void SetHeight(int height) = 0;
};

