//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORTSUBJECT_H
#define LII_VIEWPORTSUBJECT_H
#include "Viewport2Subscriber.h"
#include "EventSource.h"

class ViewportSubject : public virtual EventSource
{
public:
    virtual void AddViewport2Subscriber(Viewport2Subscriber &subscriber) = 0;
    virtual void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) = 0;
    virtual void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) = 0;
    virtual void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) = 0;
    virtual void NotifyOnViewportReset(const Viewport2EventInfo &event) = 0;
};
#endif //LII_VIEWPORTSUBJECT_H
