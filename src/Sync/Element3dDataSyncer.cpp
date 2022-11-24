//
// Created by Erik on 18/04/22.
//

#include "Element3dDataSyncer.h"
#include <algorithm>
#include <execution>
#include <future>
#include "Element3d.h"
#include "RenderEventInfo.h"

void Element3dDataSyncer::InternalSyncData(MultiTree<std::unique_ptr<Element3d>> &node)
{
    RenderEventInfo e{&renderingPool};
    //Causes crash CRASH1
    std::future<void> syncResult = std::async(std::launch::async, [&]{ node.GetValue()->OnRenderSync(e);});
    std::for_each(std::execution::par, node.GetNodes().begin(), node.GetNodes().end(), [&](std::unique_ptr<MultiTree<std::unique_ptr<Element3d>>>& i)
    {
        InternalSyncData(*i);
    });
    syncResult.wait();
}

void Element3dDataSyncer::SyncData(MultiTree<std::unique_ptr<Element3d>> &node)
{
    syncFinished = false;
    InternalSyncData(node);
    std::lock_guard<std::mutex>syncFinishedGuard{syncFinishedMutex};
    syncFinished = true;
    syncFinishedSignal.notify_all();
}

void Element3dDataSyncer::WaitForSync()
{
    std::unique_lock<std::mutex>syncFinishedGuard{syncFinishedMutex};
    syncFinishedSignal.wait(syncFinishedGuard, [=]{return syncFinished;});
}

Element3dDataSyncer::Element3dDataSyncer(OpenGLRenderingPool &renderingPool) : renderingPool(renderingPool)
{

}
