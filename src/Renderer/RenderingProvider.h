//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERINGPROVIDER_H
#define LII_RENDERINGPROVIDER_H
class CoreWindow;
#include "EntryStateSubscriber.h"
class RenderingProvider : public EntryStateSubscriber
{
public:
    virtual void Render() = 0;
    virtual void OnInit(CoreWindow& coreWindow) = 0;
    virtual void OnDestroy(CoreWindow& coreWindow) = 0;
    virtual void OnRemove(CoreWindow& coreWindow) = 0;
    virtual void WaitForSyncToFinish() = 0;
};


#endif //LII_RENDERINGPROVIDER_H
