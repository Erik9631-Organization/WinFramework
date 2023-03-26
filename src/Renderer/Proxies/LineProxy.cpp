//
// Created by erik9 on 12/11/2022.
//

#include "LineProxy.h"
#include "Commands.h"
#include "LineModel.h"

void LineProxy::SetStartPosition(const glm::vec3& position)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, lineModel->GetModelId());
    renderMessage->SetSubMessageId(SubCommands::SetStartPoint);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void LineProxy::SetEndPosition(const glm::vec3& position)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, lineModel->GetModelId());
    renderMessage->SetSubMessageId(SubCommands::SetEndPoint);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void LineProxy::SetWidth(float width)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(width, lineModel->GetModelId());
    renderMessage->SetSubMessageId(SubCommands::SetWidth);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

const glm::vec4 & LineProxy::GetStartPoint()
{
    return lineModel->GetStartPoint();
}

const glm::vec4 & LineProxy::GetEndPoint()
{
    return lineModel->GetEndPoint();
}

const float &LineProxy::GetWidth()
{
    return lineModel->GetWidth();
}

size_t & LineProxy::GetAssociatedModelId()
{
    return lineModel->GetModelId();
}

void LineProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    this->renderingConsumer = consumer;
    this->lineModel = dynamic_cast<LineModel*>(model);
}

void LineProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{

}
