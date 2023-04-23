//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGCONSUMER_H
#define LII_RENDERINGCONSUMER_H
#include "RenderMessage.h"
#include <memory>
class RenderingConsumer
{
public:
    virtual void ReceiveCommand(std::unique_ptr<RenderMessage> message) = 0;
};


#endif //LII_RENDERINGCONSUMER_H
