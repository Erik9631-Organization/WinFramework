//
// Created by Erik on 11/02/22.
//

#include "UiTreeDataSyncer.h"
#include <execution>
#include <future>
#include "UiElement.h"
#include "DrawData2D.h"
#include "MultiTree.h"
#include "WindowsCore.h"

void UiTreeDataSyncer::InternalSyncData(MultiTree<std::unique_ptr<UiElement>> &node)
{
    //Notify current node, then go to the next one.
    DrawData2D defaultDrawData;
    std::future<void> syncResult = std::async(std::launch::async, [&]{node.GetValue()->OnSync(defaultDrawData);});
    std::for_each(std::execution::par, node.GetNodes().begin(), node.GetNodes().end(), [&](std::unique_ptr<MultiTree<std::unique_ptr<UiElement>>>& i)
    {
        InternalSyncData(*i);
    });
    syncResult.wait();
}

void UiTreeDataSyncer::WaitForSync()
{
    std::unique_lock<std::mutex>syncFinishedGuard{syncFinishedMutex};
    syncFinishedSignal.wait(syncFinishedGuard, [=]{return syncFinished;});
}

void UiTreeDataSyncer::SyncData(MultiTree<std::unique_ptr<UiElement>> &node)
{
    syncFinished = false;
    InternalSyncData(node);
    std::lock_guard<std::mutex>syncFinishedGuard{syncFinishedMutex};
    syncFinished = true;
    syncFinishedSignal.notify_all();
}
