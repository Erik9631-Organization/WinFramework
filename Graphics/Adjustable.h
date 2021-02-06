#pragma once
#include "Resizable.h"
#include "Movable.h"
#include "UpdateSubscriber.h"

class Adjustable : public Resizable, public Movable, public UpdateSubscriber
{

};

