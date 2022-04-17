//
// Created by Erik on 12/04/22.
//

#ifndef LII_DESTROYSUBSCRIBER_H
#define LII_DESTROYSUBSCRIBER_H
#include "DestroyEventInfo.h"

class DestroySubscriber
{
public:
    virtual void OnObjectDestroyed(DestroyEventInfo* e) = 0;
    ~DestroySubscriber() = default;
};

#endif //LII_DESTROYSUBSCRIBER_H
