//
// Created by Erik on 18/04/22.
//

#ifndef LII_STARTSUBJECTBEHAVIOR_H
#define LII_STARTSUBJECTBEHAVIOR_H
#include "OnStartSubject.h"
#include "StartSubscriber.h"
#include <vector>
/**
 * TODO REFACTOR Default event behavior, use templates
 * Use templates instead of default behaviors as event based behavior is always same.
 * The behaviors themselves don't even need to have an interface
 */
class StartSubjectBehavior : public OnStartSubject
{
public:
    void AddOnStartSubscriber(StartSubscriber *subscriber) override;
    void RemoveOnStartSubscriber(StartSubscriber *subscriber) override;
    void NotifyOnStartSubscribers() override;
private:
    std::vector<StartSubscriber*> subscribers;
};


#endif //LII_STARTSUBJECTBEHAVIOR_H
