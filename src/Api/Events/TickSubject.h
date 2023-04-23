//
// Created by Erik on 14/03/22.
//

#ifndef LII_TICKSUBJECT_H
#define LII_TICKSUBJECT_H
#include <memory>

class OnTickSubscriber;

class TickSubject
{
public:
    virtual void AddOnTickSubscriber(OnTickSubscriber *subscriber) = 0;
    virtual void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) = 0;
    virtual void NotifyOnTick() = 0;
};


#endif //LII_TICKSUBJECT_H
