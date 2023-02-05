//
// Created by erik9 on 1/3/2023.
//

#ifndef LII_MESSAGEGENERATEMODEL_H
#define LII_MESSAGEGENERATEMODEL_H
#include <future>
#include <functional>
#include "RenderProxy.h"

template<class T>
class MessageGenerateModel
{
private:
    T proxy = nullptr;
    bool isCallbackSet = false;
public:
    MessageGenerateModel(T renderProxyParam)
    {
        proxy = renderProxyParam;
    }

    T GetRendererProxy()
    {
        return proxy;
    }

};


#endif //LII_MESSAGEGENERATEMODEL_H
