//
// Created by Erik on 05/02/22.
//

#include "DrawData2D.h"
#include "Vector2.h"

int DrawData2D::GetDataType() const
{
    return DataType::drawData2D;
}

DrawData2D::DrawData2D(Vector2 position, Vector2 size) : position(position), size(size)
{
    this->position = position;
    this->size = size;
}

Vector2 DrawData2D::GetPosition() const
{
    return position;
}

Vector2 DrawData2D::GetSize() const
{
    return size;
}

DrawData2D::DrawData2D(const DrawData2D& data)
{
    this->position = data.position;
    this->size = data.size;
}

DrawData2D::DrawData2D()
{
    this->position = {0, 0};
    this->size = {0, 0};
}
