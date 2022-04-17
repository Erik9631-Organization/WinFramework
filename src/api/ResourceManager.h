//
// Created by Erik on 13/04/22.
//

#ifndef LII_RESOURCEMANAGER_H
#define LII_RESOURCEMANAGER_H
#include "Taggable.h"
#include <any>

class ResourceManager : public Taggable
{
public:
    virtual std::any GetResource(std:: string tag) = 0;
};
#endif //LII_RESOURCEMANAGER_H
