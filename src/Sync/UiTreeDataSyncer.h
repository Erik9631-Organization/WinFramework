//
// Created by Erik on 11/02/22.
//

#ifndef LII_UITREEDATASYNCER_H
#define LII_UITREEDATASYNCER_H
#include <mutex>

#include "MultiTree.h"
class UiElement;

class UiTreeDataSyncer
{
private:
    std::condition_variable syncFinishedSignal;
    bool syncFinished = true;
    void InternalSyncData(MultiTree<std::unique_ptr<UiElement>> &node);
    std::mutex syncFinishedMutex;
public:
    void SyncData(MultiTree<std::unique_ptr<UiElement>> &node);
    void WaitForSync();
};

#endif //LII_UITREEDATASYNCER_H
