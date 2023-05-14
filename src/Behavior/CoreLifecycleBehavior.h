//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_CORELIFECYCLEBEHAVIOR_H
#define LII_CORELIFECYCLEBEHAVIOR_H

#include <vector>
#include "CoreLifecycleSubject.h"

class CoreLifecycleBehavior : public CoreLifecycleSubject
{
private:
    std::vector<CoreLifecycleSubscriber*> subscribers;
    enum class State
    {
        BEFORE_INIT,
        INIT,
        START,
        STOP,
        DESTROY
    };
    State currentState = State::BEFORE_INIT;
    void NotifyNewSubscriber(CoreLifecycleSubscriber* subscriber);
    Core& associatedCore;
public:
    explicit CoreLifecycleBehavior(Core& associatedCore);
    void NotifyOnCoreInit(const EventCoreLifecycleInfo& e) override;
    void NotifyOnCoreStart(const EventCoreLifecycleInfo& e) override;
    void NotifyOnCoreStop(const EventCoreLifecycleInfo& e) override;
    void NotifyOnCoreDestroy(const EventCoreLifecycleInfo& e) override;
    void AddCoreLifecycleSubscriber(CoreLifecycleSubscriber* subscriber) override;
    void RemoveCoreLifecycleSubscriber(CoreLifecycleSubscriber* subscriber) override;
};


#endif //LII_CORELIFECYCLEBEHAVIOR_H
