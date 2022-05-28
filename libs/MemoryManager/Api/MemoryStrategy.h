//
// Created by Erik on 07/05/22.
//

#ifndef REDBLACKMEMORYMANAGER_MEMORYSTRATEGY_H
#define REDBLACKMEMORYMANAGER_MEMORYSTRATEGY_H

class MemoryStrategy
{
public:
    virtual size_t CreateMemoryChunk(const size_t &size) = 0;
    virtual void EraseMemoryChunk(size_t chunkAddress) = 0;

    /**
     *
     * @param data
     * @param size
     * @param offset
     * template<typename T, typename MetaDataType>
     * void EraseData(MetaData<MetaDataType>& metaData, size_t& usedMemory, const size_t& memoryStartAddr);
     */

    /**
    *
    * @param data
    * @param size
    * @param offset
    * template<typename T, typename MetaDataType, typename ... Args>
    * T* WriteData(MetaData<MetaDataType>& metaData, size_t& usedMemory, const size_t& memoryStartAddr, Args ... args);
    */

    /**
     *
     * template<typename T>
     * T* ReadData(const size_t& offset, const size_t& memoryStartAddr);
     */

    /**
     *
     * \param memoryStartAddr The start address of the memory block to manage. If 0, then no start address is was assigned
     * \param oldSize The old size of the memoryStartAddr block. If 0, then no memory was previously assigned
     * \param newSize The new size of the memoryBlock
     */
    virtual size_t Realloc(const size_t &memoryStartAddr, const size_t &oldSize, const size_t &newSize) = 0;
};

#endif //REDBLACKMEMORYMANAGER_MEMORYSTRATEGY_H
