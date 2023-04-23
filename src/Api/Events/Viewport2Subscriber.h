//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2SUBSCRIBER_H
#define LII_VIEWPORT2SUBSCRIBER_H
#include "Viewport2Event.h"

class Viewport2Subscriber
{
public:
    virtual void OnViewPortChanged(Viewport2Event& event) = 0;
};


#endif //LII_VIEWPORT2SUBSCRIBER_H
