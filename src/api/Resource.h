//
// Created by Erik on 09/03/22.
//

#ifndef LII_RESOURCE_H
#define LII_RESOURCE_H
#include "Taggable.h"

class Resource : public Taggable
{
public:
    virtual void Load() = 0;
    virtual void Unload() = 0;
    virtual const bool& IsLoaded() = 0;
};

#endif //LII_RESOURCE_H