//
// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERMESSAGE_H
#define LII_RENDERMESSAGE_H
#include <any>
#include <memory>

class RenderMessage
{
private:
    std::any data;
    unsigned long long messageId;
    template<class dataType>
    RenderMessage(const long long messageId, dataType data)
    {
        this->messageId = messageId;
        this->data = std::make_any<dataType>(data);
    }
public:
    template<class dataType>
    static std::unique_ptr<RenderMessage> Create(const long long messageId, dataType data)
    {
        auto renderMessage = new RenderMessage(messageId, data);
        return std::unique_ptr<RenderMessage>(renderMessage);
    }

    template<class dataType>
    dataType GetData()
    {
        return std::any_cast<dataType>(data);
    }

    const unsigned long long& GetId() const
    {
        return messageId;
    }

};
#endif //LII_RENDERMESSAGE_H
