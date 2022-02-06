//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERINGPROVIDER_H
#define LII_RENDERINGPROVIDER_H
class CoreWindow;
#include "OnSyncCompleteSubject.h"

class RenderingProvider : public OnSyncCompleteSubject
{
public:
    virtual void AssignRenderer() = 0;
    virtual void OnInit(CoreWindow& coreWindow) = 0;
    virtual void OnDestroy(CoreWindow& coreWindow) = 0;
    virtual void OnRemove(CoreWindow& coreWindow) = 0;
};


#endif //LII_RENDERINGPROVIDER_H
