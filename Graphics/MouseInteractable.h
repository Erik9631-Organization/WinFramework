#pragma once
#include "MouseStateSubject.h"
#include "Collidable.h"
#include "Activatable.h"
class MouseInteractable : public MouseStateSubject, public Collidable, public Activatable
{
};

