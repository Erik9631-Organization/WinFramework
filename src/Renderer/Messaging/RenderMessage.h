//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERMESSAGE_H
#define LII_RENDERMESSAGE_H
#include <any>
#include <memory>
#include "Commands.h"
#include "RenderMessageSender.h"

class RenderMessage
{
private:
    std::any data;
    Commands messageId = Commands::None;
    size_t receiverId = -1;
    SubCommands subMessageId = SubCommands::None;
    RenderMessageSender *sender = nullptr;
public:

    RenderMessageSender* GetRenderMessageSender()
    {
        return sender;
    }

    const long long int & GetReceiverId() const
    {
        return receiverId;
    }

    void SetReceiverId(size_t receiverId)
    {
        RenderMessage::receiverId = receiverId;
    }

    template<class dataType>
    RenderMessage(Commands messageId, dataType data, RenderMessageSender* sender = nullptr)
    {
        this->sender = sender;
        this->messageId = messageId;
        this->data = std::make_any<dataType>(data);
    }

    template<class dataType>
    static std::unique_ptr<RenderMessage> Create(Commands messageId, dataType data, RenderMessageSender* sender = nullptr)
    {
        auto renderMessage = new RenderMessage(messageId, data, sender);
        return std::unique_ptr<RenderMessage>(renderMessage);
    }

    template<class dataType>
    static std::unique_ptr<RenderMessage> CreatePropertyMessage(dataType data, long long int receiverId)
    {
        return CreatePropertyMessage(data, nullptr, receiverId);
    }

    template<class dataType>
    static std::unique_ptr<RenderMessage> CreatePropertyMessage(dataType data, RenderMessageSender* sender = nullptr, long long int receiverId = 0)
    {
        auto renderMessage = new RenderMessage(Commands::Property, data, sender);
        renderMessage->receiverId = receiverId;
        return std::unique_ptr<RenderMessage>(renderMessage);
    }

    void SetSubMessageId(SubCommands subMessageId)
    {
        this->subMessageId = subMessageId;
    }

    template<class dataType>
    dataType GetData()
    {
        return std::any_cast<dataType>(data);
    }

    const Commands & GetMessageId() const
    {
        return messageId;
    }

    const SubCommands & GetSubMessageId() const
    {
        return subMessageId;
    }

};
#endif //LII_RENDERMESSAGE_H
