//
// Created by erik9 on 11/16/2022.
//

#ifndef LII_COREMANAGER_H
#define LII_COREMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include "Factory.h"
#include <optional>

class CoreManager
{
private:
    static std::unique_ptr<CoreManager> coreManager;
    std::string defaultCoreFactory = "Core";
public:
    CoreManager();
    std::unique_ptr<Core> Create(const std::string &tag, std::optional<std::any> args);
    std::unique_ptr<Core> Create(std::optional<std::any> args);
    std::unordered_map<std::string, std::unique_ptr<Factory<Core>>> coreFactories;
    void RegisterCoreFactory(std::unique_ptr<Factory<Core>> coreFactory);
    void UnRegisterCoreFactory(const std::string &tag);
    void SetDefaultCoreFactory(const std::string &tag);
    static CoreManager* GetCoreManager();
};


#endif //LII_COREMANAGER_H
