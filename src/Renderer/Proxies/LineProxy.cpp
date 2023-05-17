//
// Created by erik9 on 12/11/2022.
//

#include <iostream>
#include "LineProxy.h"
#include "Commands.h"
#include "LineModel.h"

void LineProxy::SetStartPosition(const glm::vec3& position)
{
    auto message = RenderMessage::CreatePropertyMessage(position, this);
    message->SetSubMessageId(SubCommands::SetStartPoint);
    messageSender.SendRenderingMessage(std::move(message));
}

void LineProxy::SetEndPosition(const glm::vec3& position)
{
    auto message = RenderMessage::CreatePropertyMessage(position, this);
    message->SetSubMessageId(SubCommands::SetEndPoint);
    messageSender.SendRenderingMessage(std::move(message));
}

void LineProxy::SetSize(float width)
{
    auto message = RenderMessage::CreatePropertyMessage(width, this);
    message->SetSubMessageId(SubCommands::SetSize);
    messageSender.SendRenderingMessage(std::move(message));
}

const glm::vec3 & LineProxy::GetStartPoint()
{
    auto tempData = messageSender.Get(SubCommands::SetStartPoint);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVec;

    return model->GetStartPoint();
}

const glm::vec3 & LineProxy::GetEndPoint()
{
    auto tempData = messageSender.Get(SubCommands::SetEndPoint);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVec;

    return model->GetEndPoint();
}

float LineProxy::GetSize()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<const float&>();
    if(model == nullptr)
        return 0.0f;

    return model->GetSize();
}

const size_t & LineProxy::GetAssociatedModelId()
{
    return model->GetModelId();
}

void LineProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    this->model = dynamic_cast<LineModel*>(model);
    if (this->model == nullptr)
    {
        std::cout << "LineProxy::OnModelCreated: model is not a LineModel" << std::endl;
        return;
    }
    messageSender.OnModelCreated(model, consumer);
}

void LineProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    messageSender.OnRenderMessageProcessed(processedCommand);
}

void LineProxy::SetVisible(bool visible)
{
    auto message = RenderMessage::CreatePropertyMessage(visible, this);
    message->SetSubMessageId(SubCommands::SetVisible);
    messageSender.SendRenderingMessage(std::move(message));
}

bool LineProxy::IsVisible()
{
    auto tempData = messageSender.Get(SubCommands::SetVisible);
    if(tempData != nullptr)
        return tempData->GetData<const bool&>();
    if(model == nullptr)
        return false;

    return model->IsVisible();
}

SubCommands LineProxy::GetModelRequestCommand()
{
    return SubCommands::RequestLine;
}

void LineProxy::SetViewportSize(const glm::vec3 &input)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(input, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportSizeChanged({GetViewportPosition(), input, this});
}

void LineProxy::SetViewportPosition(const glm::vec3 &input)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(input, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportPositionChanged({input, GetViewportSize(), this});
}

const glm::vec3 & LineProxy::GetViewportSize()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec3&>();
    if(model == nullptr)
        return defaultVec;
    return model->GetViewportPosition();
}

const glm::vec3 & LineProxy::GetViewportPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec3&>();
    if(model == nullptr)
        return defaultVec;
    return model->GetViewportPosition();
}

void LineProxy::ResetViewport()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportReset({GetViewportPosition(), GetViewportSize(), this});
}

void LineProxy::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    viewPortSubscribers.push_back(&subscriber);

}

void LineProxy::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    viewPortSubscribers.erase(std::remove(viewPortSubscribers.begin(), viewPortSubscribers.end(), &subscriber), viewPortSubscribers.end());
}

void LineProxy::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportSizeChanged(event);
}

void LineProxy::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportPositionChanged(event);
}

bool LineProxy::IsViewportSet() const
{
    return model->IsViewportSet();
}

void LineProxy::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportReset(event);
}

void LineProxy::SetColor(const glm::ivec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(color, this);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

const glm::ivec4 &LineProxy::GetColor()
{
    auto tempData = messageSender.Get(SubCommands::SetColor);
    if(tempData != nullptr)
        return tempData->GetData<const glm::ivec4&>();
    if(model == nullptr)
        return defaultColorVec;
    return model->GetColor();
}
