//
// Created by Erik on 08/10/22.
//

#ifndef LII_EVENTATTRIBUTEINFO_H
#define LII_EVENTATTRIBUTEINFO_H
#include <any>
#include "Event.h"

class EventAttributeInfo : public Event
{
private:
    int index = 0;
    long long int value;
    EventSource* source;
public:
    [[nodiscard]] int GetIndex() const;
    [[nodiscard]] long long int GetValue() const;
    EventAttributeInfo(int index, long long int value, EventSource *src);
    [[nodiscard]] EventSource *GetSource() const override;

};


#endif //LII_EVENTATTRIBUTEINFO_H
