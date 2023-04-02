//
// Created by erik9 on 2/4/2023.
//

#include "RenderingProxyMessageSender.h"
#include "RenderingModel.h"
#include "RenderingConsumer.h"
#include <iostream>

RenderingProxyMessageSender::RenderingProxyMessageSender()
{
    preInitMessages = new moodycamel::ConcurrentQueue<std::unique_ptr<RenderMessage>>();
}


void RenderingProxyMessageSender::Add(const SubCommands &subCommand, RenderMessage *message)
{
    //Add can be accessed while rendering thread is calling remove
    std::lock_guard<std::mutex>lock{mapLock};
    copyOnWriteMap[static_cast<int>(subCommand)] = message;
}

//Called from the rendering thread
void RenderingProxyMessageSender::Remove(const SubCommands &subCommand)
{
    std::lock_guard<std::mutex>lock{mapLock};
    copyOnWriteMap[static_cast<int>(subCommand)] = nullptr;
}

RenderMessage *RenderingProxyMessageSender::Get(const SubCommands &subCommand)
{
    return copyOnWriteMap[static_cast<int>(subCommand)];
}

//Called from the rendering thread
void RenderingProxyMessageSender::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    this->Remove(processedCommand);
}

void RenderingProxyMessageSender::SendRenderingMessage(std::unique_ptr<RenderMessage> message)
{
    Add(message->GetSubMessageId(), message.get());
    std::lock_guard<std::mutex> lock(modelSetMutex);
    if(model == nullptr)
    {
        if(preInitMessages == nullptr)
        {
            std::cout << "preInitMessages is null!" << std::endl;
            return;
        }
        preInitMessages->enqueue(std::move(message));
        return;
    }

    message->SetReceiverId(model->GetModelId());
    TrySendCommand(std::move(message));
}

void RenderingProxyMessageSender::OnModelCreated(RenderingModel *model, RenderingConsumer *renderingConsumer)
{
    if(preInitMessages == nullptr)
    {
        std::cout << "preInitMessages is null!" << std::endl;
        return;
    }
    this->renderingConsumer = renderingConsumer;

    std::unique_ptr<RenderMessage> message;
    std::lock_guard<std::mutex> lock(modelSetMutex);
    while(preInitMessages->try_dequeue(message))
    {
        message->SetReceiverId(model->GetModelId());
        TrySendCommand(std::move(message));
    }
    this->model = model;

    //Throw away the queue as it is no longer needed after we have the model
    delete preInitMessages;
    preInitMessages = nullptr;
}

void RenderingProxyMessageSender::TrySendCommand(std::unique_ptr<RenderMessage> message)
{
    if(renderingConsumer == nullptr)
    {
        std::cout << "Error, renderingConsumer is null!" << std::endl;
        return;
    }

    return renderingConsumer->ReceiveCommand(std::move(message));
}
