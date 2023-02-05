//
// Created by erik9 on 2/4/2023.
//

#ifndef LII_COMMANDCOPYONWRITEMAP_H
#define LII_COMMANDCOPYONWRITEMAP_H
#include <unordered_map>
#include "Commands.h"
#include "RenderMessage.h"
#include <mutex>

class CommandCopyOnWriteMap
{
private:
    std::mutex mapLock;
    std::unordered_map<SubCommands, RenderMessage*> copyOnWriteMap;
    unsigned int size = 0;
public:
    CommandCopyOnWriteMap(size_t size);
    void Add(const SubCommands &subCommand, RenderMessage* message);
    void Remove(const SubCommands &subCommand);
    RenderMessage* Get(const SubCommands &subCommand);
};


#endif //LII_COMMANDCOPYONWRITEMAP_H
