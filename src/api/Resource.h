//
// Created by Erik on 09/03/22.
//

#ifndef LII_RESOURCE_H
#define LII_RESOURCE_H
#include "Taggable.h"

class Resource : public Taggable
{
public:
    virtual void LoadResource() = 0;
    virtual void UnloadResource() = 0;
    virtual const bool& IsLoaded() = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};

#endif //LII_RESOURCE_H
