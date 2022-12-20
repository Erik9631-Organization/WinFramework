//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_MESSAGEIDS_H
#define LII_MESSAGEIDS_H

enum CommandIds
{
   RequestRectangle,
   RequestModel,
   RequestProxy,
   RequestEllipse,
   RequestLine,
   RectangleProperty,
   ModelProperty,
   EllipseProperty,
   LineProperty,
};

enum PropertyCommandIds
{
    None,
    SetSize,
    SetPosition,
    SetTransform,
    SetWidth,
    SetHeight,
    SetX,
    SetY,
    TransformX,
    TransformY,
    SetColor,
};

#endif //LII_MESSAGEIDS_H
