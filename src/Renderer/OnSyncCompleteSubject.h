//
// Created by Erik on 06/02/22.
//

#ifndef LII_ONSYNCCOMPLETESUBJECT_H
#define LII_ONSYNCCOMPLETESUBJECT_H

class OnSyncCompleteSubscriber;

class OnSyncCompleteSubject
{
public:
    virtual void NotifyOnSyncComplete(OnSyncCompleteSubject& src) = 0;
    virtual void AddOnSyncSubscriber(OnSyncCompleteSubscriber& subscriber) = 0;
    virtual void RemoveOnSyncSubscriber(OnSyncCompleteSubscriber& subscriber) = 0;
};


#endif //LII_ONSYNCCOMPLETESUBJECT_H
