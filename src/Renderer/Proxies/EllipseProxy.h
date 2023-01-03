//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_ELLIPSEPROXY_H
#define LII_ELLIPSEPROXY_H
#include "RendererProxy.h"
#include "Movable.h"
#include "vec2.hpp"

class EllipseProxy : public virtual Movable, public virtual RendererProxy
{
private:
    unsigned long long associatedModelId;
public:
    glm::vec2 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec2 GetAbsolutePosition() override;

    void SetPosition(glm::vec2 position, bool emit) override;

    void SetPosition(glm::vec2 position) override;

    void SetPosition(float x, float y, bool emit) override;

    void SetPosition(float x, float y) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec2 offset, bool emit) override;

    void SetTranslate(glm::vec2 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec2 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    unsigned long long int &GetAssociatedModelId() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;
};


#endif //LII_ELLIPSEPROXY_H
