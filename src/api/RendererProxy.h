//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RENDERERPROXY_H
#define LII_RENDERERPROXY_H
class RendererProxy
{
public:
    virtual unsigned long long& GetAssociatedModelId() = 0;
    virtual ~RendererProxy() = 0;
};


#endif //LII_RENDERERPROXY_H
