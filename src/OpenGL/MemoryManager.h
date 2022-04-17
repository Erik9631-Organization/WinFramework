//
// Created by Erik on 27/03/22.
//

#ifndef LII_MEMORYMANAGER_H
#define LII_MEMORYMANAGER_H
#include "MeshMemoryManager.h"
#include "FloatVertexAttribute.h"
#include <unordered_map>
#include "MeshMemoryManager.h"
#include <memory>
#include "VboProperties.h"

namespace OpenGL
{
    class DefaultMemoryManager;
    class MemoryManager
    {
    private:
        static DefaultMemoryManager* manager;
    public:
        virtual std::unique_ptr<MeshMemoryManager> & Aquire(const long long& id) = 0;
        virtual MeshMemoryManager& Aquire(const unsigned int &usage, std::unique_ptr<VboProperties> attributes) = 0;
        static MemoryManager& GetMemoryManager();
    };
}


#endif //LII_MEMORYMANAGER_H
