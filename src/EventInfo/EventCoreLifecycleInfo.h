//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_EVENTCORELIFECYCLEINFO_H
#define LII_EVENTCORELIFECYCLEINFO_H


#include "Event.h"
class Core;

class EventCoreLifecycleInfo : public Event
{
private:
    Core* core = nullptr;
    EventSource* src = nullptr;
public:
    EventCoreLifecycleInfo(Core* core, EventSource* source);
    [[nodiscard]] EventSource *GetSource() const override;
    Core* GetCore() const;
};


#endif //LII_EVENTCORELIFECYCLEINFO_H
