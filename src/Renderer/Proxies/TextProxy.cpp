//
// Created by erik9 on 12/11/2022.
//

#include "TextProxy.h"
#include "EventMoveInfo.h"

glm::vec4 TextProxy::GetPosition()
{
    return glm::vec4();
}

float TextProxy::GetX()
{
    return 0;
}

float TextProxy::GetY()
{
    return 0;
}

float TextProxy::GetZ()
{
    return 0;
}

float TextProxy::GetW()
{
    return 0;
}

float TextProxy::GetAbsoluteX()
{
    return 0;
}

float TextProxy::GetAbsoluteY()
{
    return 0;
}

glm::vec4 TextProxy::GetAbsolutePosition()
{
    return glm::vec4();
}

void TextProxy::SetPosition(glm::vec4 position, bool emit)
{

}

void TextProxy::SetPosition(glm::vec4 position)
{

}

void TextProxy::SetPosition(float x, float y, float z, float w, bool emit)
{

}

void TextProxy::SetPosition(float x, float y, float z, float w)
{

}

void TextProxy::SetX(float x, bool emit)
{

}

void TextProxy::SetX(float x)
{

}

void TextProxy::SetY(float y, bool emit)
{

}

void TextProxy::SetY(float y)
{

}

void TextProxy::SetZ(float z, bool emit)
{

}

void TextProxy::SetZ(float z)
{

}

void TextProxy::SetW(float w, bool emit)
{

}

void TextProxy::SetW(float w)
{

}

void TextProxy::SetTranslate(glm::vec4 offset, bool emit)
{

}

void TextProxy::SetTranslate(glm::vec4 offset)
{

}

void TextProxy::SetTranslateX(float x, bool emit)
{

}

void TextProxy::SetTranslateX(float x)
{

}

void TextProxy::SetTranslateY(float y, bool emit)
{

}

void TextProxy::SetTranslateY(float y)
{

}

glm::vec4 TextProxy::GetTranslate()
{
    return glm::vec4();
}

float TextProxy::GetTranslateX()
{
    return 0;
}

float TextProxy::GetTranslateY()
{
    return 0;
}

void TextProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{

}

size_t &TextProxy::GetAssociatedModelId()
{
    return id;
}

void TextProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{

}


void TextProxy::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{

}

void TextProxy::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{

}

void TextProxy::NotifyOnMoveSubscribers(EventMoveInfo e)
{

}

void TextProxy::OnMove(EventMoveInfo e)
{

}
