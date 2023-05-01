//
// Created by Erik on 08/10/22.
//

#ifndef LII_EVENTCURSORLOCKINFO_H
#define LII_EVENTCURSORLOCKINFO_H
#include "Event.h"

class EventCursorLockInfo : public Event
{
private:
    bool cursorLockInfo;
    EventSource* src;
public:
    EventCursorLockInfo(bool cursorLockInfo, EventSource *src);
    [[nodiscard]] const bool& GetCursorLockInfo() const;
    [[nodiscard]] EventSource *GetSource() const override;

};


#endif //LII_EVENTCURSORLOCKINFO_H
