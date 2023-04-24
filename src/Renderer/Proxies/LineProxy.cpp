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

const size_t & LineProxy::GetAssociatedModelId()
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

void LineProxy::SetVisible(bool visible)
{

}

bool LineProxy::IsVisible()
{
    return false;
}

SubCommands LineProxy::GetModelRequestCommand()
{
    return SubCommands::RequestLine;
}

void LineProxy::SetViewportSize(const glm::vec4 &vec4)
{

}

void LineProxy::SetViewportPosition(const glm::vec4 &vec4)
{

}

const glm::vec4 & LineProxy::GetViewportSize()
{
    auto val = glm::vec4{0,0,0,0};
    return val;
}

const glm::vec4 & LineProxy::GetViewportPosition()
{
    auto val = glm::vec4{0,0,0,0};
    return val;
}

void LineProxy::ResetViewport()
{

}

void LineProxy::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.push_back(&subscriber);
}

void LineProxy::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.erase(std::remove(viewPortSubscribers.begin(), viewPortSubscribers.end(), &subscriber), viewPortSubscribers.end());
}

void LineProxy::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for(auto subscriber : viewPortSubscribers)
        subscriber->OnViewportSizeChanged(event);
}

void LineProxy::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for(auto subscriber : viewPortSubscribers)
        subscriber->OnViewportPositionChanged(event);
}

bool LineProxy::IsViewportSet() const
{
    return lineModel->IsViewportSet();
}

void LineProxy::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for(auto subscriber : viewPortSubscribers)
        subscriber->OnViewportReset(event);
}
