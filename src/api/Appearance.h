//
// Created by erik9 on 1/23/2023.
//

#ifndef LII_APPEARANCE_H
#define LII_APPEARANCE_H
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "MouseInteractable.h"
#include "MountedSubscriber.h"

class Appearance : public MoveSubscriber, public ResizeSubscriber, public MountedSubscriber
{

};


#endif //LII_APPEARANCE_H
