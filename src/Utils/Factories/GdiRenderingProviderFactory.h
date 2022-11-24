//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_GDIRENDERINGPROVIDERFACTORY_H
#define LII_GDIRENDERINGPROVIDERFACTORY_H
#include "Factory.h"

class GdiRenderingProviderFactory : public Factory<RenderingProvider>
{
private:
    std::string tag = "GdiRenderingProvider";
public:
    const std::string &GetTag() override;
    void SetTag(const std::string &tag) override;
    std::unique_ptr<RenderingProvider> Create() override;
    std::unique_ptr<RenderingProvider> Create(std::any args) override;
};


#endif //LII_GDIRENDERINGPROVIDERFACTORY_H
