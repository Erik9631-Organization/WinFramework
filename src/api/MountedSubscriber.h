//
// Created by erik9 on 12/7/2022.
//

#ifndef LII_MOUNTEDSUBSCRIBER_H
#define LII_MOUNTEDSUBSCRIBER_H
class Presenter;

class MountedSubscriber
{
public:
    virtual void OnMounted(Presenter& presenter, UiElement& element) = 0;
};


#endif //LII_MOUNTEDSUBSCRIBER_H
