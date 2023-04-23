#pragma once
#include "Events/MouseStateSubject.h"
#include "Collidable.h"
#include "Activatable.h"
/**
 * This interface is implemented by all the classes that can interact with the mouse.
 * The class unifies the following interfaces: MouseStateSubject, Collidable, Activatable,
 */
class MouseInteractable : public virtual MouseStateSubject, public virtual Collidable, public virtual Activatable
{
};

