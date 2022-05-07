//
// Created by Erik on 18/04/22.
//

#ifndef LII_STARTSUBJECTBEHAVIOR_H
#define LII_STARTSUBJECTBEHAVIOR_H
#include "OnStartSubject.h"
#include "StartSubscriber.h"
#include <vector>
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
