//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERINGPROVIDER_H
#define LII_RENDERINGPROVIDER_H
class CoreWindowFrame;

class RenderingProvider
{
public:
    virtual void AssignRenderer() = 0;
    virtual void OnInit(CoreWindowFrame& coreWindowFrame) = 0;
};


#endif //LII_RENDERINGPROVIDER_H
