//
// Created by erik9 on 12/7/2022.
//

#ifndef LII_MOUNTEDSUBJECT_H
#define LII_MOUNTEDSUBJECT_H
#include "MountedSubscriber.h"
class Presenter;

class MountedSubject
{
public:
    virtual void AddOnMountedSubscriber(MountedSubscriber &subscriber) = 0;
    virtual void RemoveOnMountedSubscriber(MountedSubscriber &subscriber) = 0;
    virtual void NotifyOnMounted(Presenter& presenter) = 0;
};


#endif //LII_MOUNTEDSUBJECT_H
