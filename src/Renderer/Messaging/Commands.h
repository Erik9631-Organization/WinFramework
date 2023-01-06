//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_COMMANDS_H
#define LII_COMMANDS_H

enum Commands
{
   RequestRectangle,
   RequestModel,
   RequestProxy,
   RequestEllipse,
   RequestLine,
   Property,
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
    SetTranslate,
    SetWidth,
    SetHeight,
    SetX,
    SetY,
    TranslateX,
    TranslateY,
    SetColor,
    SetStartPoint,
    SetEndPoint,
    SetFill,
};

#endif //LII_COMMANDS_H
