//
// Created by Erik on 29/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_MEMORYMANAGER_H
#define REDBLACKMEMORYMANAGER_MEMORYMANAGER_H
#include <map>

namespace MemManager
{
    class MemoryManager
    {
        virtual void* GetData(const size_t& offset, const size_t& size) = 0;
        virtual const std::multimap<size_t, size_t>& GetFreeMemoryMap() const = 0;
        virtual const std::map<size_t, size_t>& GetFreeOffsetMap() const = 0;
        virtual const size_t& GetUsedMemory() const = 0;
        virtual const size_t GetFreeMemory() = 0;
        template<class >
    };

} // MemManager

#endif //REDBLACKMEMORYMANAGER_MEMORYMANAGER_H
