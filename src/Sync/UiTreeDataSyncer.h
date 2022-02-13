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
    void InternalSyncData(MultiTree<UiElement&>& node);
    std::mutex syncFinishedMutex;
public:
    void SyncData(MultiTree<UiElement&>& node);
    void WaitForSync();
};

#endif //LII_UITREEDATASYNCER_H
