//
// Created by Erik on 30/03/22.
//
#include "MemoryManager.h"
#include "DefaultMemoryManager.h"
using namespace OpenGL;

DefaultMemoryManager* MemoryManager::manager = new DefaultMemoryManager();

MemoryManager &MemoryManager::GetMemoryManager()
{
    return *manager;
}
