//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERMESSAGE_H
#define LII_RENDERMESSAGE_H
#include <any>
#include <memory>
#include "Commands.h"

class RenderMessage
{
private:
    std::any data;
    Commands messageId = Commands::None;
    long long int receiverId = -1;
    SubCommands subMessageId = SubCommands::None;

public:
    const long long int & GetReceiverId() const
    {
        return receiverId;
    }

    void SetReceiverId(long long int receiverId)
    {
        RenderMessage::receiverId = receiverId;
    }

    template<class dataType>
    RenderMessage(Commands messageId, dataType data)
    {
        this->messageId = messageId;
        this->data = std::make_any<dataType>(data);
    }

    template<class dataType>
    static std::unique_ptr<RenderMessage> Create(Commands messageId, dataType data)
    {
        auto renderMessage = new RenderMessage(messageId, data);
        return std::unique_ptr<RenderMessage>(renderMessage);
    }

    template<class dataType>
    static std::unique_ptr<RenderMessage> CreatePropertyMessage(long long int receiverId, dataType data)
    {
        auto renderMessage = new RenderMessage(Commands::Property, data);
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

    const Commands & GetId() const
    {
        return messageId;
    }

    const SubCommands & GetSubId() const
    {
        return subMessageId;
    }

};
#endif //LII_RENDERMESSAGE_H
