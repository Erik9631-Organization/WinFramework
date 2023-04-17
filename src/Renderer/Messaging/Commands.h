//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_COMMANDS_H
#define LII_COMMANDS_H

enum class Commands : unsigned char
{
    None,
   RequestRectangle,
   RequestModel,
   RequestEllipse,
   RequestText,
   RequestLine,
   Property,
   Redraw,
   Quit,
};

enum class SubCommands : unsigned char
{
    None,
    RequestRectangle,
    RequestEllipse,
    RequestText,
    RequestLine,
    SetSize,
    SetPosition,
    SetTranslate,
    SetWidth,
    SetHeight,
    SetX,
    SetY,
    SetTranslateX,
    SetTranslateY,
    SetViewPortSize,
    SetViewPortPosition,
    ResetViewPort,
    SetColor,
    SetThickness,
    SetStartPoint,
    SetEndPoint,
    SetFontSize,
    SetFontLineAlignment,
    SetFontAlignment,
    SetFill,
    SetText,
    SetFontFamily,
    CommandCount,
};

#endif //LII_COMMANDS_H
