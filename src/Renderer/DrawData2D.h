//
// Created by Erik on 05/02/22.
//

#ifndef LII_DRAWDATA2D_H
#define LII_DRAWDATA2D_H
#include "DrawData.h"
#include "Vector2.h"

class DrawData2D : public DrawData
{
public:
    DrawData2D(const DrawData2D& data);
    DrawData2D();

    DrawData2D(Vector2 position, Vector2 size);
    int GetDataType() const override;
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
private:
    Vector2 position;
    Vector2 size;
};


#endif //LII_DRAWDATA2D_H
