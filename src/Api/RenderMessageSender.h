//
// Created by erik9 on 1/10/2023.
//

#ifndef LII_RENDERMESSAGESENDER_H
#define LII_RENDERMESSAGESENDER_H
#include "Commands.h"
class RenderMessageSender
{
public:
    virtual void OnRenderMessageProcessed(const SubCommands& processedCommand) = 0;
};
#endif //LII_RENDERMESSAGESENDER_H
