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
    DrawData2D() = default;

    DrawData2D(glm::vec3 position, glm::vec4 size);
    int GetDataType() const override;
    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] glm::vec4 GetSize() const;
private:
    glm::vec3 position{0};
    glm::vec4 size{0};
};


#endif //LII_DRAWDATA2D_H
