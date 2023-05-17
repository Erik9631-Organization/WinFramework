//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORTSUBJECT_H
#define LII_VIEWPORTSUBJECT_H
#include "ViewportSubscriber.h"
#include "EventSource.h"

class ViewportSubject : public virtual EventSource
{
public:
    virtual void AddViewportSubscriber(ViewportSubscriber &subscriber) = 0;
    virtual void RemoveViewportSubscriber(ViewportSubscriber &subscriber) = 0;
    virtual void NotifyOnViewportSizeChanged(const ViewportEventInfo &event) = 0;
    virtual void NotifyOnViewportPositionChanged(const ViewportEventInfo &event) = 0;
    virtual void NotifyOnViewportReset(const ViewportEventInfo &event) = 0;
};
#endif //LII_VIEWPORTSUBJECT_H
