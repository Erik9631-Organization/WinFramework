//
// Created by Erik on 16/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
#define REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
#include "MetaData.hpp"
template<class MemoryStrategyType, class MetaDataType>
class MemoryManager;

template<class Type, class MemoryStrategyType, class MetaDataType = size_t>
class ManagedPtr
{
public:
    ManagedPtr(MemoryManager<MemoryStrategyType, MetaDataType>& manager, MetaData<MetaDataType>& objectMetaData) :
    manager(manager),
    objectMetaData(objectMetaData){}

    Type& operator * ()
    {
        return *manager.GetData<Type>(objectMetaData.GetOffset());
    }

    Type* operator ->()
    {
        return manager.GetData<Type>(objectMetaData.GetOffset());
    }

    void Free()
    {
        manager.Remove<Type>(objectMetaData);
    }


private:
    MetaData<MetaDataType>& objectMetaData;
    MemoryManager<MemoryStrategyType, MetaDataType>& manager;
};


#endif //REDBLACKMEMORYMANAGER_MANAGEDPTR_HPP
