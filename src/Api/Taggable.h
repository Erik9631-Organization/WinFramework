//
// Created by Erik on 26/03/22.
//

#ifndef LII_TAGGABLE_H
#define LII_TAGGABLE_H
#include <string>
class Taggable
{
public:
    virtual const std::string& GetTag() = 0;
    virtual void SetTag(const std::string& tag) = 0;
    ~Taggable() = default;
};

#endif //LII_TAGGABLE_H