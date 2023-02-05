//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RENDERPROXY_H
#define LII_RENDERPROXY_H
#include "RenderMessageSender.h"
class RenderingModel;
class RenderingConsumer;


class RenderProxy : public RenderMessageSender
{
public:
    virtual size_t & GetAssociatedModelId() = 0;
    virtual void OnModelCreated(RenderingModel *model) = 0;
    virtual void SetRenderingConsumer(RenderingConsumer *consumer) = 0;
    virtual ~RenderProxy() = default;
};


#endif //LII_RENDERPROXY_H
