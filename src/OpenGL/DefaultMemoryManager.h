//
// Created by Erik on 27/03/22.
//

#ifndef LII_DEFAULTMEMORYMANAGER_H
#define LII_DEFAULTMEMORYMANAGER_H
#include "MemoryManager.h"
#include "FloatVertexAttribute.h"
#include "MeshMemoryManager.h"
#include <unordered_map>

namespace OpenGL
{
    class DefaultMemoryManager : public MemoryManager
    {
    private:
        std::unique_ptr<MeshMemoryManager> uniqueNullPtr;
        std::unordered_map<unsigned int, std::unique_ptr<MeshMemoryManager>> memoryMap;
        static DefaultMemoryManager manager;
    public:
        std::unique_ptr<MeshMemoryManager> & Aquire(const long long int &id) override;
        MeshMemoryManager &Aquire(const unsigned int &usage, std::unique_ptr<VertexAttributeGroup> attributes) override;
    };
}


#endif //LII_DEFAULTMEMORYMANAGER_H
