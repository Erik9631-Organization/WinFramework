//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_BUFFERRENDERER_H
#define LII_BUFFERRENDERER_H
#include "CoreLifecycleSubscriber.h"
#include "RenderingBase.h"
#include "Injectable.h"
#include <glm.hpp>
#include "Buffer.h"

class BufferRenderer : public CoreLifecycleSubscriber, public RenderingBase, public LiiInjector::Injectable
{
public:
    virtual void DrawFragment(const glm::ivec3& position, const glm::ivec4 &color) = 0;
    virtual unsigned int CreateColor(const glm::ivec4& color) = 0;
    virtual Lii::DataTypes::Buffer<unsigned int> GetScreenBuffer() = 0;
};


#endif //LII_BUFFERRENDERER_H
