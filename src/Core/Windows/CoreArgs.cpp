//
// Created by erik9 on 11/2/2022.
//

#include "CoreArgs.h"
#include <memory>
#include "Window.h"

any CoreArgs::Create(std::string name, long style, Window *associatedWindow)
{
    return std::make_any<CoreArgs>(name, style, associatedWindow);
}

CoreArgs::CoreArgs(std::string name, long style, Window *window)
{
    this->name = name;
    this->style = style;
    associatedWindow = window;
}
