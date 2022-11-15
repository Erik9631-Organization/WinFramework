//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_RENDERINGPROVIDERFACTORY_H
#define LII_RENDERINGPROVIDERFACTORY_H
#include "RenderingProvider.h"
#include <memory>
#include <string>
#include "Taggable.h"

class RenderingProviderFactory : public Taggable
{
public:
    virtual std::unique_ptr<RenderingProvider> Create() = 0;
    virtual ~RenderingProviderFactory() = default;
};


#endif //LII_RENDERINGPROVIDERFACTORY_H
