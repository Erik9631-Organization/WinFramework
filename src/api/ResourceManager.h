//
// Created by Erik on 13/04/22.
//

#ifndef LII_RESOURCEMANAGER_H
#define LII_RESOURCEMANAGER_H
#include "Taggable.h"
#include <map>
#include "Resource.h"

class ResourceManager : public Taggable
{
public:
    virtual Resource * GetResource(std:: string tag) = 0;
    virtual std::unique_ptr<std::vector<Resource *>> GetLoadedResources() = 0;
    virtual std::unique_ptr<std::vector<Resource *>> GetUnloadedResources() = 0;
    virtual std::unique_ptr<std::vector<Resource *>> GetResources() = 0;
    virtual void LoadResource(const std::string& resource) = 0;
    virtual void UnloadResource(const std::string& resource) = 0;
};
#endif //LII_RESOURCEMANAGER_H
