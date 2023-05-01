//
// Created by Erik on 08/10/22.
//

#include "EventAttributeInfo.h"

EventAttributeInfo::EventAttributeInfo(int index, long long int value, const std::any &src)
{
    this->index = index;
    this->value = value;
    this->src = std::move(src);
}

const std::any &EventAttributeInfo::GetSrc() const
{
    return src;
}

long long int EventAttributeInfo::GetValue() const
{
    return value;
}

int EventAttributeInfo::GetIndex() const
{
    return index;
}
