//
// Created by Erik on 12/04/22.
//

#ifndef LII_DESTROYSUBJECT_H
#define LII_DESTROYSUBJECT_H
#include "DestroySubscriber.h"
#include "DestroyEventInfo.h"

class DestroySubject
{
public:
    virtual void NotifyOnDestroy(DestroyEventInfo* e) = 0;
    virtual void AddOnDestroySubscriber(DestroySubscriber* subject) = 0;
    virtual void RemoveOnDestroySubscriber(DestroySubscriber* subject) = 0;
};


#endif //LII_DESTROYSUBJECT_H
