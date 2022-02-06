//
// Created by Erik on 06/02/22.
//

#ifndef LII_ONSYNCCOMPLETESUBSCRIBER_H
#define LII_ONSYNCCOMPLETESUBSCRIBER_H
#include "OnSyncCompleteSubject.h"


class OnSyncCompleteSubscriber
{
public:
    virtual void OnSyncComplete(OnSyncCompleteSubject& src) = 0;
};


#endif //LII_ONSYNCCOMPLETESUBSCRIBER_H
