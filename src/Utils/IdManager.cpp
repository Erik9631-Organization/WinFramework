//
// Created by Erik on 29/06/22.
//

#include "IdManager.h"

IdManager::IdManager(const unsigned int &size) : maxSize(size)
{

}

IdManager::IdManager() : idList()
{

}

unsigned int IdManager::AquireId()
{
    idGenerator++;
    if(maxSize != 0)
        if(idGenerator > maxSize)
            idGenerator = 0;

    while(idList.find(idGenerator) != idList.end())
        idGenerator++;

    return idGenerator;
}

unsigned int IdManager::FreeId(const unsigned int &id)
{
    auto it = idList.find(id);
    if(it != idList.end())
        idList.erase(it);

    return 0;
}
