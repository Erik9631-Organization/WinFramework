//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CORELIFECYCLESUBSCRIBER_H
#define LII_CORELIFECYCLESUBSCRIBER_H
#include "EventCoreLifecycleInfo.h"

class CoreLifecycleSubscriber
{
public:
    virtual ~CoreLifecycleSubscriber() = default;
    virtual void OnCoreInit(const EventCoreLifecycleInfo& e) = 0;
    virtual void OnCoreStart(const EventCoreLifecycleInfo& e) = 0;
    virtual void OnCoreStop(const EventCoreLifecycleInfo& e) = 0;
    virtual void OnCoreDestroy(const EventCoreLifecycleInfo& e) = 0;

};


#endif //LII_CORELIFECYCLESUBSCRIBER_H
