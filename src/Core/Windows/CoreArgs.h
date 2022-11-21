//
// Created by erik9 on 11/2/2022.
//

#ifndef LII_COREARGS_H
#define LII_COREARGS_H
#include <string>
#include <any>
class Window;

class CoreArgs
{
public:
    CoreArgs(std::string name, long style, Window *window);
    static std::any Create(std::string name, long style, Window *associatedWindow);
    std::string name;
    long style;
    Window* associatedWindow;
};


#endif //LII_COREARGS_H
