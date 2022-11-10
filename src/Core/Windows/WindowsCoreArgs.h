//
// Created by erik9 on 11/2/2022.
//

#ifndef LII_WINDOWSCOREARGS_H
#define LII_WINDOWSCOREARGS_H
#include <string>
#include <any>

class WindowsCoreArgs
{
public:
    WindowsCoreArgs(std::string name, long style);
    static std::any Create(std::string name, long style);
    std::string name;
    long style;
};


#endif //LII_WINDOWSCOREARGS_H
