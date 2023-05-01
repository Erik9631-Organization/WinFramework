//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2SUBSCRIBER_H
#define LII_VIEWPORT2SUBSCRIBER_H
#include "Viewport2EventInfo.h"

class Viewport2Subscriber
{
public:
    virtual void OnViewportSizeChanged(const Viewport2EventInfo &event) = 0;
    virtual void OnViewportPositionChanged(const Viewport2EventInfo &event) = 0;
    virtual void OnViewportReset(const Viewport2EventInfo &event) = 0;
};


#endif //LII_VIEWPORT2SUBSCRIBER_H
