//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CORELIFECYCLESUBJECT_H
#define LII_CORELIFECYCLESUBJECT_H


#include "EventSource.h"
#include "EventCoreLifecycleInfo.h"
#include "CoreLifecycleSubscriber.h"

class CoreLifecycleSubject : public EventSource
{
public:
    virtual void NotifyOnCoreInit(const EventCoreLifecycleInfo& e) = 0;
    virtual void NotifyOnCoreStart(const EventCoreLifecycleInfo& e) = 0;
    virtual void NotifyOnCoreStop(const EventCoreLifecycleInfo& e) = 0;
    virtual void NotifyOnCoreDestroy(const EventCoreLifecycleInfo& e) = 0;
    virtual void AddCoreLifecycleSubscriber(CoreLifecycleSubscriber* subscriber) = 0;
    virtual void RemoveCoreLifecycleSubscriber(CoreLifecycleSubscriber* subscriber) = 0;
};


#endif //LII_CORELIFECYCLESUBJECT_H
