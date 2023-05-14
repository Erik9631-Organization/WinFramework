//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RENDERPROXY_H
#define LII_RENDERPROXY_H
#include "RenderMessageSender.h"
#include "MountedSubscriber.h"
#include "Viewport.h"

class RenderingModel;
class RenderingConsumer;


class RenderProxy : public RenderMessageSender, public Viewport
{
public:
    virtual const size_t & GetAssociatedModelId() = 0;
    virtual void OnModelCreated(RenderingModel *model, RenderingConsumer *consumer) = 0;
    virtual void SetVisible(bool visible) = 0;
    virtual bool IsVisible() = 0;
    virtual SubCommands GetModelRequestCommand() = 0;
    virtual ~RenderProxy() = default;
};


#endif //LII_RENDERPROXY_H
