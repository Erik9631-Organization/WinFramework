//
// Created by Erik on 18/04/22.
//

#ifndef LII_ELEMENT3DDATASYNCER_H
#define LII_ELEMENT3DDATASYNCER_H
#include <mutex>
#include "MultiTree.h"
#include "OpenGLRenderingPool.h"

class Element3d;
class Element3dDataSyncer
{
private:
    std::condition_variable syncFinishedSignal;
    bool syncFinished = true;
    void InternalSyncData(MultiTree<std::unique_ptr<Element3d>> &node);
    std::mutex syncFinishedMutex;
    OpenGLRenderingPool& renderingPool;
public:
    Element3dDataSyncer(OpenGLRenderingPool& renderingPool);
    void SyncData(MultiTree<std::unique_ptr<Element3d>> &node);
};


#endif //LII_ELEMENT3DDATASYNCER_H
