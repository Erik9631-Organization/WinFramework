#pragma once
#include "Events/ResizeSubject.h"
#include "glm.hpp"

/**
 * An interface for all the classes that can be resized.
 * The interface also defines that every resizable has to support an event stream (Byt enforcing the ResizeSubject interface)
 */
class Resizable : public ResizeSubject
{
public:
    /**
     * Returns the viewPortPosition of the object.
     * \return returns a viewPortPosition object which specifies the width and height
     */
    [[nodiscard]] virtual const glm::vec4 &GetSize() const = 0;

    /**
     * Sets the viewPortPosition of the object
     * \param size the viewPortPosition object which specifies the width and height of the target object.
     */
    virtual void SetSize(const glm::vec4 &size, bool emit = true) = 0;
};