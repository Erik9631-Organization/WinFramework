//
// Created by erik9 on 2/4/2023.
//

#ifndef LII_RENDERINGPROXYMESSAGESENDER_H
#define LII_RENDERINGPROXYMESSAGESENDER_H
#include <unordered_map>
#include "Commands.h"
#include "RenderMessage.h"
#include "concurrentqueue.h"
#include "RenderingModel.h"
#include <mutex>

class RenderingProxyMessageSender : public RenderMessageSender
{
private:
    std::mutex mapLock;
    std::unordered_map<SubCommands, RenderMessage*> copyOnWriteMap;
    unsigned int size = 0;
    void Add(const SubCommands &subCommand, RenderMessage* message);
    void Remove(const SubCommands &subCommand);
    moodycamel::ConcurrentQueue<std::unique_ptr<RenderMessage>>* preInitMessages = nullptr;
    RenderingConsumer* renderingConsumer = nullptr;
    RenderingModel* model = nullptr;
    std::mutex modelSetMutex;
    void TrySendCommand(std::unique_ptr<RenderMessage> message);
public:
    RenderingProxyMessageSender(size_t size);
    void SendRenderingMessage(std::unique_ptr<RenderMessage> message);
    RenderMessage* Get(const SubCommands &subCommand);
    void OnRenderMessageProcessed(const SubCommands &processedCommand) override;
    void OnModelCreated(RenderingModel *model, RenderingConsumer *renderingConsumer);
};


#endif //LII_RENDERINGPROXYMESSAGESENDER_H
