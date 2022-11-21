//
// Created by erik9 on 11/16/2022.
//

#include "CoreFactory.h"
#include "WindowsCore.h"
#include "CoreArgs.h"

std::unique_ptr<Core> CoreFactory::Create()
{
    return CreateWindowsCore();
}

const std::string &CoreFactory::GetTag()
{
    return tag;
}

void CoreFactory::SetTag(const std::string &tag)
{
    this->tag = tag;
}

unique_ptr<Core> CoreFactory::Create(std::any args)
{
    return CreateWindowsCore(args);
}

std::unique_ptr<Core> CoreFactory::CreateWindowsCore(std::any args)
{
    return WindowsCore::Create(std::move(args));
}

std::unique_ptr<Core> CoreFactory::CreateWindowsCore()
{
    auto args = CoreArgs::Create("window", WS_OVERLAPPEDWINDOW, nullptr);
    return CreateWindowsCore(args);
}
