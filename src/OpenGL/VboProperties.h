//
// Created by Erik on 29/03/22.
//

#ifndef LII_VBOPROPERTIES_H
#define LII_VBOPROPERTIES_H

#include <glew.h>
#include "VertexAttribute.h"
#include <vector>
#include <map>
#include "Hash.h"
#include "FloatVertexAttribute.h"
#include <memory>

class VboProperties : Hashable
{
private:
    std::map<size_t, std::unique_ptr<VertexAttribute>> vertexAttributes;
    unsigned int verticeSize = 0;
    GLenum usage;

    //For hash
    size_t hash = 0;

public:
    VboProperties(std::vector<std::unique_ptr<VertexAttribute>> &attributes, GLenum usage = GL_STATIC_DRAW);
    const size_t & GetHash() const override;
    const GLenum& GetUsage() const;
    void Create();
    void Enable();
    void Disable();
    unsigned int GetVerticeSize();

};


#endif //LII_VBOPROPERTIES_H
