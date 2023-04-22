//
// Created by erik9 on 12/10/2022.
//

#ifndef LII_ASYNCRENDERCOMMANDHANDLER_H
#define LII_ASYNCRENDERCOMMANDHANDLER_H
#include <future>
#include <functional>
#include "RenderProxy.h"
#include "EllipseProxy.h"
#include "LineProxy.h"
#include "RectangleProxy.h"
#include "TextProxy.h"
#include "RenderingConsumer.h"
#include "Renderer.h"
#include "ModelProxy.h"
#include <memory>
#include "Commands.h"

class AsyncRenderCommandHandler : virtual public RenderingConsumer
{
public:
    virtual void RequestModel(RenderProxy &proxy) = 0;

    virtual void SetViewportSize(int width, int height) = 0;
    virtual void SetViewportSize(const glm::ivec2& size) = 0;
    virtual void OnInit(Core& core) = 0;
    virtual void OnDestroy(Core& core) = 0;
    virtual void SwapScreenBuffer() = 0;

};
#endif //LII_ASYNCRENDERCOMMANDHANDLER_H