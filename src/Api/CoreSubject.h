//
// Created by Erik on 08/10/22.
//

#ifndef LII_CORESUBJECT_H
#define LII_CORESUBJECT_H
#include <any>
#include "EventMoveInfo.h"
#include "EventResizeInfo.h"
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
class CoreSubscriber;

class CoreSubject
{
private:

public:
    virtual void NotifyCoreOnDestroy(std::any src) = 0;
    virtual void NotifyCoreOnClose(std::any src) = 0;
    virtual void NotifyCoreOnMove(EventMoveInfo e) = 0;
    virtual void NotifyCoreOnResize(EventResizeInfo e) = 0;
    virtual void NotifyCoreOnMouseMove(EventMouseStateInfo e) = 0;
    virtual void NotifyCoreOnMouseLButtonDown(EventMouseStateInfo e) = 0;
    virtual void NotifyCoreOnMouseLButtonUp(EventMouseStateInfo e) = 0;
    virtual void NotifyCoreOnMousePressed(EventMouseStateInfo e) = 0;
    virtual void NotifyCoreOnKeyUp(EventKeyStateInfo e) = 0;
    virtual void NotifyCoreOnKeyDown(EventKeyStateInfo e) = 0;
    virtual void NotifyCoreOnKeyPressed(EventKeyStateInfo e) = 0;
    virtual void NotifyCoreOnWheelMoved(EventKeyStateInfo e) = 0;
    virtual void AddCoreSubscriber(CoreSubscriber* subscriber) = 0;
    virtual void RemoveCoreSubscriber(CoreSubscriber* subscriber) = 0;
};
#endif //LII_CORESUBJECT_H
