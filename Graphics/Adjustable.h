#pragma once
#include "Resizable.h"
#include "Movable.h"
#include "UpdateSubscriber.h"
/**
 * An interface for all classes that can be moved as well as resized.
 * It enforces the Resizable, Movable and the UpdateSubscriber interface.
 */
class Adjustable : public Resizable, public Movable, public UpdateSubscriber
{

};

