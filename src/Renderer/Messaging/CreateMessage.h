//
// Created by erik9 on 1/3/2023.
//

#ifndef LII_CREATEMESSAGE_H
#define LII_CREATEMESSAGE_H
#include <future>
#include <functional>
#include "RenderProxy.h"

template<class T>
class CreateMessage
{
private:
    std::promise<T> rendererProxyPromise;
    std::function<void(T)> futureCallback;
public:
    CreateMessage(std::promise<T> renderProxyParam)
    {
        rendererProxyPromise = std::move(renderProxyParam);
    }
    CreateMessage(std::function<void(T)> futureCallbackParam)
    {
        futureCallback = std::move(futureCallbackParam);
    }

    std::promise<T>& GetRendererProxyPromise()
    {
        return rendererProxyPromise;
    }
    std::function<void(T)>& GetFutureCallback()
    {
        return rendererProxyPromise;
    }

};


#endif //LII_CREATEMESSAGE_H
