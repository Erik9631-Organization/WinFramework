//
// Created by Erik on 05/02/22.
//

#include "DrawData2D.h"

int DrawData2D::GetDataType() const
{
    return DataType::drawData2D;
}

DrawData2D::DrawData2D(glm::vec3 position, glm::vec3 size) : position(position), size(size)
{
    this->position = position;
    this->size = size;
}

glm::vec3 DrawData2D::GetPosition() const
{
    return position;
}

glm::vec3 DrawData2D::GetSize() const
{
    return size;
}

DrawData2D::DrawData2D(const DrawData2D& data)
{
    this->position = data.position;
    this->size = data.size;
}