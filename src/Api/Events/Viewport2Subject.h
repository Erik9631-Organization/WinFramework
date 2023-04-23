//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2SUBJECT_H
#define LII_VIEWPORT2SUBJECT_H
#include "Viewport2Subscriber.h"

class Viewport2Subject
{
public:
    virtual void AddViewport2Subscriber(Viewport2Subscriber* subscriber) = 0;
    virtual void RemoveViewport2Subscriber(Viewport2Subscriber* subscriber) = 0;
    virtual void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) = 0;
    virtual void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) = 0;
};
#endif //LII_VIEWPORT2SUBJECT_H
