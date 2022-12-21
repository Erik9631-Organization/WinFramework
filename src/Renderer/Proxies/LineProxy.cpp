//
// Created by erik9 on 12/11/2022.
//

#include "LineProxy.h"
#include "Commands.h"

void LineProxy::SetStartPosition(const glm::vec3& position)
{
    auto renderMessage = RenderMessage::Create(Commands::LineProperty, position);
    renderMessage->SetSubMessageId(PropertyCommandIds::SetStartPoint);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void LineProxy::SetEndPosition(const glm::vec3& position)
{
    auto renderMessage = RenderMessage::Create(Commands::LineProperty, position);
    renderMessage->SetSubMessageId(PropertyCommandIds::SetEndPoint);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}
