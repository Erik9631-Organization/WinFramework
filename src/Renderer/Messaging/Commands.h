//
// Created by erik9 on 12/19/2022.
//

#ifndef LII_COMMANDS_H
#define LII_COMMANDS_H

enum class Commands
{
    None,
   RequestRectangle,
   RequestModel,
   RequestEllipse,
   RequestLine,
   Property,
   Redraw,
   Quit,
};

enum class SubCommands
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
    SetViewPortSize,
    SetViewPortPosition,
    ResetViewPort,
    SetColor,
    SetThickness,
    SetStartPoint,
    SetEndPoint,
    SetFill,
};

#endif //LII_COMMANDS_H
