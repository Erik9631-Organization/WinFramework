//
// Created by Erik on 05/02/22.
//

#ifndef LII_DRAWDATA_H
#define LII_DRAWDATA_H


class DrawData
{
public:
    enum DataType
    {
        drawData2D
    };
    virtual int GetDataType() const = 0;
};


#endif //LII_DRAWDATA_H
