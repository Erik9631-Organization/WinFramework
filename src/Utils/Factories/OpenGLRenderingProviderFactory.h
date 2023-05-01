//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_OPENGLRENDERINGPROVIDERFACTORY_H
#define LII_OPENGLRENDERINGPROVIDERFACTORY_H
#include "Factory.h"

class OpenGLRenderingProviderFactory : public Factory<Renderer>
{
private:
    std::string tag = "OpenGLRenderingProvider";
public:
    std::unique_ptr<Renderer> Create() override;
    const std::string &GetTag() override;
    void SetTag(const std::string &tag) override;
    std::unique_ptr<Renderer> Create(std::any args) override;
};


#endif //LII_OPENGLRENDERINGPROVIDERFACTORY_H
