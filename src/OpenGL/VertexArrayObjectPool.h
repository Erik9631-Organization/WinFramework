//
// Created by Erik on 26/03/22.
//

#ifndef LII_VERTEXARRAYOBJECTPOOL_H
#define LII_VERTEXARRAYOBJECTPOOL_H
#include <unordered_map>
#include <DefaultVertexAttribute.h>
#include <memory>

namespace OpenGL
{
    class VertexArrayObjectPool
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<DefaultVertexAttribute>> vertexAttributeMap;
        static const VertexArrayObjectPool& attributePool;
    public:
        static VertexArrayObjectPool GetVertexAttributePool();
        DefaultVertexAttribute& Aquire(const std::string& tag);
    };
}


#endif //LII_VERTEXARRAYOBJECTPOOL_H
