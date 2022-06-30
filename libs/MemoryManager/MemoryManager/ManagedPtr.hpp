//
// Created by Erik on 16/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
#define REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
#include "MetaData.hpp"
namespace MemManager
{
    template<class MemoryStrategyType>
    class MemoryManager;

    template<class Type, class MemoryStrategyType>
    class ManagedPtr
    {
    public:
        ManagedPtr(MemoryManager<MemoryStrategyType>* manager, MetaData* objectMetaData) :
            manager(manager),
            objectMetaData(objectMetaData)
        {}

        ManagedPtr() = default;

        Type &operator*() const
        {
            return *(manager->GetData<Type>(objectMetaData->GetOffset()));
        }

        Type *operator->() const
        {
            return manager->GetData<Type>(objectMetaData->GetOffset());
        }

        Type operator [] (const size_t& value)
        {
            return *(manager->GetData<Type>(objectMetaData->GetOffset() + sizeof(Type)*value));
        }

        const MetaData* GetMetaData() const
        {
            return objectMetaData;
        }

        void Free()
        {
            manager->Remove<Type>(*objectMetaData);
        }

    private:
        MetaData* objectMetaData = nullptr;
        MemoryManager<MemoryStrategyType>* manager = nullptr;
    };
}

#endif //REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
