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
};

enum SubCommandIds
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
};

#endif //LII_MESSAGEIDS_H
