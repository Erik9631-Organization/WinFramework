//
// Created by Erik on 08/10/22.
//

#include "EventAttributeInfo.h"

EventAttributeInfo::EventAttributeInfo(const int &index, const long long int &value, std::any src)
{
    this->index = index;
    this->value = value;
    this->src = std::move(src);
}

const std::any &EventAttributeInfo::GetSrc() const
{
    return src;
}

const long long int & EventAttributeInfo::GetValue() const
{
    return value;
}

const int &EventAttributeInfo::GetIndex() const
{
    return index;
}
