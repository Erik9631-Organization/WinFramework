//
// Created by Erik on 05/02/22.
//

#ifndef LII_DRAWDATA2D_H
#define LII_DRAWDATA2D_H
#include "DrawData.h"
#include <glm.hpp>

class DrawData2D : public DrawData
{
public:
    DrawData2D(const DrawData2D& data);
    DrawData2D();

    DrawData2D(glm::vec2 position, glm::vec2 size);
    int GetDataType() const override;
    glm::vec2 GetPosition() const;
    glm::vec2 GetSize() const;
private:
    glm::vec2 position;
    glm::vec2 size;
};


#endif //LII_DRAWDATA2D_H
