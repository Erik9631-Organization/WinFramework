//
// Created by Erik on 08/10/22.
//

#include "EventAttributeInfo.h"

EventAttributeInfo::EventAttributeInfo(int index, long long int value, EventSource *src)
{
    this->index = index;
    this->value = value;
    this->source = src;
}

long long int EventAttributeInfo::GetValue() const
{
    return value;
}

int EventAttributeInfo::GetIndex() const
{
    return index;
}

EventSource * EventAttributeInfo::GetSource() const
{
    return source;
}
