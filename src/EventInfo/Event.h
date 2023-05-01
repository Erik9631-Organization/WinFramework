//
// Created by erik9 on 5/1/2023.
//

#ifndef LII_EVENT_H
#define LII_EVENT_H
#include "EventSource.h"

class Event
{
public:
    [[nodiscard]] virtual EventSource* GetSource() const = 0;
    virtual ~Event() = default;
};


#endif //LII_EVENT_H
