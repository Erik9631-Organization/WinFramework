//
// Created by Erik on 28/05/22.
//

#ifndef LII_GPUMEMORYSTRATEGY_H
#define LII_GPUMEMORYSTRATEGY_H

#include <cstddef>
#include "MemoryStrategy.h"
#include "MetaData.hpp"
#include <glew.h>
#include "VertexAttributeGroup.h"
#include "GpuMemoryStrategySubscriber.h"

class GpuMemoryStrategy : public MemManager::MemoryStrategy
{
private:
    unsigned int bufferId = 0;
    unsigned int vaoId = 0;
    VertexAttributeGroup* properties;
    GLenum usage;
    std::vector<GpuMemoryStrategySubscriber*> subscribers;

    void NotifyOnCopy(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr)
    {
        for(auto i : subscribers)
        {
            i->OnCopyData(metaData, usedMemory, memoryStartAddr);
        }
    }

    void NotifyOnWrite(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr)
    {
        for(auto i : subscribers)
        {
            i->OnWriteData(metaData, usedMemory, memoryStartAddr);
        }
    }

    void NotifyOnErase(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr)
    {
        for(auto i : subscribers)
        {
            i->OnEraseData(metaData, usedMemory, memoryStartAddr);
        }
    }

    void CreateVao()
    {
        glDeleteVertexArrays(1, &vaoId);
        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);
    }

    void BindVaoToBoundBuffers()
    {
        properties->Create();
        properties->Enable();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    }

public:
    void AddGpuAddGpuMemoryStrategySubscriber(GpuMemoryStrategySubscriber* subscriber)
    {
        subscribers.push_back(subscriber);
    }

    void RemoveGpuMemoryStrategySubscriber(GpuMemoryStrategySubscriber* subscriber)
    {
        for(auto it = subscribers.begin(); it < subscribers.end(); it++)
        {
            if(*it == subscriber)
            {
                subscribers.erase(it);
                return;
            }
        }
    }

    GpuMemoryStrategy(VertexAttributeGroup* properties = nullptr, GLenum usage = GL_STATIC_DRAW) :
    usage(usage),
    properties{properties}{}

    void SetVaoId(const unsigned int& vaoId)
    {
        this->vaoId = vaoId;
    }

    const unsigned int& GetVaoId()
    {
        return vaoId;
    }


    size_t CreateMemoryChunk(const size_t &size) override
    {
        if(properties != nullptr)
            CreateVao();

        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, size, NULL, this->usage);

        if(properties != nullptr)
            BindVaoToBoundBuffers();


        if(vaoId)
            glBindVertexArray(0);
        return bufferId;
    }

    size_t Realloc(const size_t &memoryStartAddr, const size_t &oldSize, const size_t &newSize) override
    {
        glBindBuffer(GL_COPY_READ_BUFFER, bufferId);
        unsigned int newBufferId = 0;
        glGenBuffers(1, &newBufferId);
        glBindBuffer(GL_COPY_WRITE_BUFFER, newBufferId);
        glBufferData(GL_COPY_WRITE_BUFFER, newSize, 0, this->usage);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, oldSize);
        glDeleteBuffers(1, &bufferId);
        bufferId = newBufferId;

        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        if(properties != nullptr)
        {
            glBindVertexArray(vaoId);
            BindVaoToBoundBuffers();
        }

        return bufferId;
    }

    template<typename T>
    void CopyData(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr, T* src)
    {
        glBindBuffer(GL_ARRAY_BUFFER, memoryStartAddr);
        glBufferSubData(GL_ARRAY_BUFFER, metaData.GetOffset(), metaData.GetSize(), src);
        usedMemory+=metaData.GetSize();
        NotifyOnCopy(metaData, usedMemory, memoryStartAddr);
    }

    template<typename T>
    void EraseData(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr)
    {
        //The data will be simply rewritten. Nothing else required here
        usedMemory-= metaData.GetSize();
        NotifyOnErase(metaData, usedMemory, memoryStartAddr);
    }

    template<typename T, typename ... Args>
    void WriteData(MemManager::MetaData& metaData, size_t& usedMemory, const size_t& memoryStartAddr, Args ... args)
    {
        //Currently not supported. DMA required
        NotifyOnWrite(metaData, usedMemory, memoryStartAddr);
    }

    template<typename T>
    T* ReadData(const size_t& offset, const size_t& memoryStartAddr)
    {
        //Currently not supported. DMA required
    }


};


#endif //LII_GPUMEMORYSTRATEGY_H
