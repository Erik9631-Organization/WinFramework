//
// Created by Erik on 30/06/22.
//

#ifndef LII_GPUMEMORYSTRATEGYSUBSCRIBER_H
#define LII_GPUMEMORYSTRATEGYSUBSCRIBER_H
#include <MetaData.hpp>

class GpuMemoryStrategySubscriber
{
public:
    virtual void OnCopyData(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr) = 0;
    virtual void OnEraseData(const MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr) = 0;
    virtual void OnWriteData(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr) = 0;
};
#endif //LII_GPUMEMORYSTRATEGYSUBSCRIBER_H
