#pragma once
#include "MouseStateSubject.h"
#include "Collidable.h"
#include "Activatable.h"
/**
 * This interface is implemented by all the classes that can interact with the mouse.
 * The class unifies the following interfaces: MouseStateSubject, Collidable, Activatable,
 */
class MouseInteractable : public MouseStateSubject, public Collidable, public Activatable
{
};

