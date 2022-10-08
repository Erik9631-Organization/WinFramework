//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERINGPROVIDER_H
#define LII_RENDERINGPROVIDER_H
class WindowsCore;
#include "EntryStateSubscriber.h"
class RenderingProvider : public EntryStateSubscriber
{
public:
    virtual void Render() = 0;
    virtual void OnInit(WindowsCore& coreWindow) = 0;
    virtual void OnDestroy(WindowsCore& coreWindow) = 0;
    virtual void OnRemove(WindowsCore& coreWindow) = 0;
    virtual void WaitForSyncToFinish() = 0;
};


#endif //LII_RENDERINGPROVIDER_H
