//
// Created by erik9 on 12/11/2022.
//

#ifndef LII_ELLIPSEPROXY_H
#define LII_ELLIPSEPROXY_H
#include "RenderProxy.h"
#include "Movable.h"
#include "vec2.hpp"
#include "RenderingModel.h"

class EllipseProxy : public virtual Movable, public virtual RenderProxy
{
private:
    RenderingModel *renderingModel;
public:
    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    glm::vec4 GetAbsolutePosition() override;

    void SetPosition(glm::vec4 position, bool emit) override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, bool emit) override;

    void SetPosition(float x, float y) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    size_t & GetAssociatedModelId() override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    ~EllipseProxy() override;
};


#endif //LII_ELLIPSEPROXY_H
