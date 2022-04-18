//
// Created by Erik on 18/04/22.
//

#ifndef LII_TICKSUBJECTBEHAVIOR_H
#define LII_TICKSUBJECTBEHAVIOR_H
#include "OnTickSubscriber.h"
#include "TickSubject.h"
#include <vector>

class TickSubjectBehavior : public TickSubject
{
private:
    std::vector<OnTickSubscriber*> subscribers;
public:
    void AddOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void NotifyOnTick() override;
};


#endif //LII_TICKSUBJECTBEHAVIOR_H
