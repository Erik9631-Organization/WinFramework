//
// Created by Erik on 18/04/22.
//

#ifndef LII_ONSTARTSUBJECT_H
#define LII_ONSTARTSUBJECT_H

class StartSubscriber;
class OnStartSubject
{
public:
    virtual void AddOnStartSubscriber(StartSubscriber* subscriber) = 0;
    virtual void RemoveOnStartSubscriber(StartSubscriber* subscriber) = 0;
    virtual void NotifyOnStartSubscribers() = 0;
};


#endif //LII_ONSTARTSUBJECT_H
