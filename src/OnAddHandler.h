//
// Created by Erik on 22/01/23.
//

#ifndef LII_ONADDHANDLER_H
#define LII_ONADDHANDLER_H
#include "AddSubject.h"
#include "OnAddSubscriber.h"
#include "EventOnAddInfo.h"
#include <vector>

template <class type>
class OnAddHandler : AddSubject<type>
{
private:
    std::vector<OnAddSubscriber<type>*> subscribers;
public:
    virtual void NotifyOnAddInfo(EventOnAddInfo<type> e) override
    {
        for (OnAddSubscriber<type>* subscriber : subscribers)
            subscriber->OnAdd(e);
    }

    virtual void AddOnAddSubscriber(OnAddSubscriber<type>& subscriber) override
    {
        subscribers.push_back(&subscriber);
    }

    virtual void RemoveOnAddSubscriber(OnAddSubscriber<type>& subscriber) override
    {
        for (auto it = subscribers.begin(); it != subscribers.end(); it++)
            if (*it == &subscriber)
            {
                subscribers.erase(it);
                return;
            }

    }
};
#endif //LII_ONADDHANDLER_H
