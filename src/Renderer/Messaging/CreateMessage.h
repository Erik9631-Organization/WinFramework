//
// Created by erik9 on 1/3/2023.
//

#ifndef LII_CREATEMESSAGE_H
#define LII_CREATEMESSAGE_H
#include <future>
#include <functional>
#include "RendererProxy.h"

template<class T>
class CreateMessage
{
private:
    std::unique_ptr<std::promise<std::unique_ptr<T>>> rendererProxyPromise;
    std::unique_ptr<std::function<void(std::unique_ptr<T>)>> futureCallback;
public:
    CreateMessage(std::unique_ptr<std::promise<std::unique_ptr<T>>> renderProxyParam)
    {
        rendererProxyPromise = std::move(renderProxyParam);
    }
    CreateMessage(std::unique_ptr<std::function<void(std::unique_ptr<T>)>> futureCallbackParam)
    {
        futureCallback = std::move(futureCallbackParam);
    }

    std::promise<std::unique_ptr<T>>* GetRendererProxyPromise()
    {
        return rendererProxyPromise.get();
    }
    std::function<void(std::unique_ptr<T>)>* GetFutureCallback()
    {
        return futureCallback.get();
    }

};


#endif //LII_CREATEMESSAGE_H
