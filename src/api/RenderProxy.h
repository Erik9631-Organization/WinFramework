//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_RENDERPROXY_H
#define LII_RENDERPROXY_H
class RenderingModel;
class RenderProxy
{
public:
    virtual unsigned long long& GetAssociatedModelId() = 0;
    virtual void SetAssociatedModel(RenderingModel *model) = 0;
    virtual ~RenderProxy() = default;
};


#endif //LII_RENDERPROXY_H
