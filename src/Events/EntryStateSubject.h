//
// Created by Erik on 02/05/22.
//

#ifndef LII_ENTRYSTATESUBJECT_H
#define LII_ENTRYSTATESUBJECT_H
#include "EntryStateSubscriber.h"

class EntryStateSubject
{
public:
    virtual void NotifyOnEntryStart() = 0;
    virtual void NotifyOnEntryEnd() = 0;
    virtual void AddEntryStateSubscriber(EntryStateSubscriber* subscriber) = 0;
    virtual void RemoveEntryStateSubscriber(EntryStateSubscriber* subscriber) = 0;
    virtual void WaitForEntryToFinish() = 0;
};


#endif //LII_ENTRYSTATESUBJECT_H
