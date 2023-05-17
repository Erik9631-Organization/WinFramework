//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORTSUBSCRIBER_H
#define LII_VIEWPORTSUBSCRIBER_H
#include "ViewportEventInfo.h"

class ViewportSubscriber
{
public:
    virtual void OnViewportSizeChanged(const ViewportEventInfo &event) = 0;
    virtual void OnViewportPositionChanged(const ViewportEventInfo &event) = 0;
    virtual void OnViewportReset(const ViewportEventInfo &event) = 0;
};


#endif //LII_VIEWPORTSUBSCRIBER_H
