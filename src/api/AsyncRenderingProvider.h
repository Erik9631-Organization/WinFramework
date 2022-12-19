//
// Created by erik9 on 12/10/2022.
//

#ifndef LII_ASYNCRENDERINGPROVIDER_H
#define LII_ASYNCRENDERINGPROVIDER_H
#include <future>
#include <functional>
#include "RendererProxy.h"
#include "EllipseProxy.h"
#include "LineProxy.h"
#include "RectangleProxy.h"
#include "TextProxy.h"
#include "RenderingConsumer.h"
#include "RenderingProvider.h"
class ModelProxy;

class AsyncRenderingProvider : virtual public RenderingConsumer, virtual public RenderingProvider
{
public:
    virtual std::future<EllipseProxy*> RequestEllipseProxy() = 0;
    virtual std::future<ModelProxy*> RequestModelProxy() = 0;
    virtual std::future<LineProxy*>  RequestLineProxy() = 0;
    virtual std::future<TextProxy*> RequestTextProxy() = 0;
    virtual std::future<RectangleProxy> RequestRectangleProxy() = 0;

    virtual void RequestEllipseProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestModelProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestLineProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestTextProxy(std::function<void(RendererProxy &)> onCreatedAction) = 0;
    virtual void RequestRectangleProxy(std::function<void(RendererProxy &)>) = 0;

};
#endif //LII_ASYNCRENDERINGPROVIDER_H