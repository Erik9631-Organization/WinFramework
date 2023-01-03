//
// Created by erik9 on 12/10/2022.
//

#ifndef LII_ASYNCRENDERCOMMANDHANDLER_H
#define LII_ASYNCRENDERCOMMANDHANDLER_H
#include <future>
#include <functional>
#include "RendererProxy.h"
#include "EllipseProxy.h"
#include "LineProxy.h"
#include "RectangleProxy.h"
#include "TextProxy.h"
#include "RenderingConsumer.h"
#include "RenderingProvider.h"
#include "ModelProxy.h"

class AsyncRenderCommandHandler : virtual public RenderingConsumer, virtual public RenderingProvider
{
public:
    virtual std::future<std::unique_ptr<EllipseProxy>> RequestEllipseProxy() = 0;
    virtual std::future<std::unique_ptr<ModelProxy>> RequestModelProxy() = 0;
    virtual std::future<std::unique_ptr<LineProxy>> RequestLineProxy() = 0;
    virtual std::future<std::unique_ptr<TextProxy>> RequestTextProxy() = 0;
    virtual std::future<std::unique_ptr<RectangleProxy>> RequestRectangleProxy() = 0;

    virtual void RequestEllipseProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestModelProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestLineProxy(std::function<void(std::unique_ptr<RendererProxy>)> onCreatedAction) = 0;
    virtual void RequestTextProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestRectangleProxy(std::function<void(std::unique_ptr<RendererProxy>)>) = 0;

};
#endif //LII_ASYNCRENDERCOMMANDHANDLER_H