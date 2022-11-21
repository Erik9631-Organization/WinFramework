//
// Created by erik9 on 11/16/2022.
//

#ifndef LII_COREFACTORY_H
#define LII_COREFACTORY_H
#include "Factory.h"
#include "Core.h"

class CoreFactory : public Factory<Core>
{
private:
    std::string tag = "Core";
    std::unique_ptr<Core> CreateWindowsCore(std::any args);
    std::unique_ptr<Core>CreateWindowsCore();

public:
    std::unique_ptr<Core> Create() override;
    const std::string &GetTag() override;
    void SetTag(const std::string &tag) override;
    std::unique_ptr<Core> Create(std::any args) override;

};


#endif //LII_COREFACTORY_H
