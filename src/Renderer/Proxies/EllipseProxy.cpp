//
// Created by erik9 on 12/11/2022.
//

#include "EllipseProxy.h"
#include "EventMoveInfo.h"

glm::vec2 EllipseProxy::GetPosition()
{
    return glm::vec2{0};
}

float EllipseProxy::GetX()
{
    return 0;
}

float EllipseProxy::GetY()
{
    return 0;
}

float EllipseProxy::GetAbsoluteX()
{
    return 0;
}

float EllipseProxy::GetAbsoluteY()
{
    return 0;
}

glm::vec2 EllipseProxy::GetAbsolutePosition()
{
    return glm::vec2{0};
}

void EllipseProxy::SetPosition(glm::vec2 position, bool emit)
{

}

void EllipseProxy::SetPosition(glm::vec2 position)
{

}

void EllipseProxy::SetPosition(float x, float y, bool emit)
{

}

void EllipseProxy::SetPosition(float x, float y)
{

}

void EllipseProxy::SetX(float x, bool emit)
{

}

void EllipseProxy::SetX(float x)
{

}

void EllipseProxy::SetY(float y, bool emit)
{

}

void EllipseProxy::SetY(float y)
{

}

void EllipseProxy::SetTranslate(glm::vec2 offset, bool emit)
{

}

void EllipseProxy::SetTranslate(glm::vec2 offset)
{

}

void EllipseProxy::SetTranslateX(float x, bool emit)
{

}

void EllipseProxy::SetTranslateX(float x)
{

}

void EllipseProxy::SetTranslateY(float y, bool emit)
{

}

void EllipseProxy::SetTranslateY(float y)
{

}

glm::vec2 EllipseProxy::GetTranslate()
{
    return glm::vec2{0};;
}

float EllipseProxy::GetTranslateX()
{
    return 0;
}

float EllipseProxy::GetTranslateY()
{
    return 0;
}

void EllipseProxy::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{

}

void EllipseProxy::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{

}

void EllipseProxy::NotifyOnMoveSubscribers(EventMoveInfo e)
{

}

EllipseProxy::~EllipseProxy()
{

}

unsigned long long int &EllipseProxy::GetAssociatedModelId()
{
    return renderingModel->GetModelId();
}
