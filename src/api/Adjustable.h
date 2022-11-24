#pragma once
#include "Resizable.h"
#include "Movable.h"
#include "Events/UpdateSubscriber.h"
/**
 * An interface for all classes that can be moved as well as resized.
 * It enforces the Resizable, Movable and the UpdateSubscriber interface.
 */

class Adjustable : virtual public Resizable, virtual public Movable, virtual public UpdateSubscriber
{

};
