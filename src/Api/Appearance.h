//
// Created by erik9 on 1/23/2023.
//

#ifndef LII_APPEARANCE_H
#define LII_APPEARANCE_H
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "MouseInteractable.h"
#include "MountedSubscriber.h"
#include "Viewport2.h"

class Appearance : public MoveSubscriber, public ResizeSubscriber, public MountedSubscriber, public Viewport2
{
public:
    virtual float GetRelativeZIndex() = 0;
    virtual void SetRelativeZIndex(float relativeZIndex) = 0;
    virtual void SetVisible(bool state) = 0;
};


#endif //LII_APPEARANCE_H
