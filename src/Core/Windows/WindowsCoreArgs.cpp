//
// Created by erik9 on 11/2/2022.
//

#include "WindowsCoreArgs.h"
#include <memory>

std::any WindowsCoreArgs::Create(std::string name, long style)
{
    return std::make_any<WindowsCoreArgs>(name, style);
}

WindowsCoreArgs::WindowsCoreArgs(std::string name, long style)
{
    this->name = name;
    this->style = style;
}
