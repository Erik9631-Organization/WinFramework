//
// Created by Erik on 08/10/22.
//

#ifndef LII_CORESUBSCRIBER_H
#define LII_CORESUBSCRIBER_H
#include <any>
#include "EventMoveInfo.h"
#include "EventResizeInfo.h"
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"

class CoreSubscriber
{
private:

public:
    virtual void CoreOnDestroy(std::any src) = 0;
    virtual void CoreOnClose(std::any src) = 0;
    virtual void CoreOnMove(EventMoveInfo e) = 0;
    virtual void CoreOnResize(EventResizeInfo e) = 0;
    virtual void CoreOnMouseMove(EventMouseStateInfo e) = 0;
    virtual void CoreOnMouseLButtonDown(EventMouseStateInfo e) = 0;
    virtual void CoreOnMouseLButtonUp(EventMouseStateInfo e) = 0;
    virtual void CoreOnMousePressed(EventMouseStateInfo e) = 0;
    virtual void CoreOnKeyUp(EventKeyStateInfo e) = 0;
    virtual void CoreOnKeyDown(EventKeyStateInfo e) = 0;
    virtual void CoreOnKeyPressed(EventKeyStateInfo e) = 0;
    virtual void CoreOnWheelMoved(EventKeyStateInfo e) = 0;
};


#endif //LII_CORESUBSCRIBER_H
