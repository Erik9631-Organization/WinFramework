//
// Created by erik9 on 12/11/2022.
//

#include "LineProxy.h"
#include "Commands.h"
#include "LineModel.h"

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

void LineProxy::SetRenderingConsumer(RenderingConsumer *consumer, unsigned long long associatedModelId)
{
    this->associatedModelId = associatedModelId;
    renderingConsumer = consumer;
}

void LineProxy::SetWidth(float width)
{
    auto renderMessage = RenderMessage::Create(Commands::LineProperty, width);
    renderMessage->SetSubMessageId(PropertyCommandIds::SetWidth);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

const glm::vec2 &LineProxy::GetStartPoint()
{
    return lineModel->GetStartPoint();
}

const glm::vec2 &LineProxy::GetEndPoint()
{
    return lineModel->GetEndPoint();
}

const float &LineProxy::GetWidth()
{
    return lineModel->GetWidth();
}

unsigned long long int &LineProxy::GetAssociatedModelId()
{
    return associatedModelId;
}

void LineProxy::SetAssociatedModel(RenderingModel *model)
{
    this->lineModel = dynamic_cast<LineModel*>(model);
}
