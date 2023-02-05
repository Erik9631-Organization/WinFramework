//
// Created by erik9 on 2/4/2023.
//

#include "CommandCopyOnWriteMap.h"

CommandCopyOnWriteMap::CommandCopyOnWriteMap(size_t size)
{
    copyOnWriteMap.reserve(size);
}
//Add can be accessed while rendering thread is calling remove
void CommandCopyOnWriteMap::Add(const SubCommands &subCommand, RenderMessage *message)
{
    std::lock_guard<std::mutex>lock{mapLock};
    copyOnWriteMap[subCommand] = message;
}
//Called from the rendering thread
void CommandCopyOnWriteMap::Remove(const SubCommands &subCommand)
{
    std::lock_guard<std::mutex>lock{mapLock};
    copyOnWriteMap.erase(subCommand);
}

RenderMessage *CommandCopyOnWriteMap::Get(const SubCommands &subCommand)
{
    auto it = copyOnWriteMap.find(subCommand);
    if(it != copyOnWriteMap.end())
        return it->second;
    return nullptr;
}
