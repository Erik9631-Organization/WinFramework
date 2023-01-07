//
// Created by erik9 on 1/3/2023.
//

#ifndef LII_CREATEMODELMESSAGE_H
#define LII_CREATEMODELMESSAGE_H
#include <future>
#include <functional>
#include "RenderProxy.h"

template<class T>
class CreateModelMessage
{
private:
    std::promise<T> rendererProxyPromise;
    std::function<void(T)> futureCallback;
    bool isCallbackSet = false;
public:
    CreateModelMessage(std::promise<T> renderProxyParam)
    {
        rendererProxyPromise = std::move(renderProxyParam);
    }
    CreateModelMessage(std::function<void(T)> futureCallbackParam)
    {
        futureCallback = std::move(futureCallbackParam);
        isCallbackSet = true;
    }

    const bool& IsCallbackSet() const
    {
        return isCallbackSet;
    }

    std::promise<T>& GetRendererProxyPromise()
    {
        return rendererProxyPromise;
    }
    std::function<void(T)>& GetFutureCallback()
    {
        return futureCallback;
    }

};


#endif //LII_CREATEMODELMESSAGE_H
